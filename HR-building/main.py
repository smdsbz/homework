#!/usr/bin/python3
from flask import Flask, render_template, url_for, redirect, request, session
from flask import make_response, flash
import sqlite3, os

app = Flask(__name__)
app.secret_key = 'DogLeeNation(2B||!2B)-->|'

######## functions ########

def getAll():
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select * from test')
	data = cursor.fetchall()
	return data

def getConditonal(column, conditon, require):
	#print('getConditional(%s,%s,%s) called' % (column,conditon,require))
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select %s from test where %s = '%s'" % (column, conditon, require))
	data = cursor.fetchall()
	#print(data)
	return data

def verify(id, passwd):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select passwd from test where id = '%s'" % id)
	correct = cursor.fetchone()
	#print(correct[0])
	if passwd == correct[0]:
		return 1
	else:
		session.pop('id', None)
		return 0

def writeDatabase():
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# EXTREAMLY-ugly line: write to database
	database.execute("update test set name = '%s', gender = '%s', qq = '%s', tel = '%s', wchat = '%s', emg = '%s', school = '%s', class = '%s', apart = '%s', depart = '%s', grp = '%s', occup = '%s', dateofjoin = '%s' where id = '%s'" % (request.form['name'], request.form['gender'], request.form['qq'], request.form['tel'], request.form['wchat'], request.form['emg'], request.form['school'], request.form['class'], request.form['apart'], request.form['depart'], request.form['group'], request.form['occup'], request.form['dateofjoin'], session['id']))
	database.commit()
	# EXTREAMLY-ugly lines end here

def grep(column, require):
	print('grep(%s,%s) called' % (column,require))
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select * from test where %s GLOB '*%s*'" % (column, require))
	data = cursor.fetchall()
	print(data)
	return data


######## route ########

@app.route('/')
def index():
	return redirect(url_for('login'))

@app.route('/login/', methods=['GET', 'POST'])
def login():
	if request.method == 'GET':
		return render_template('login.html');
	elif request.method == 'POST':
		session['id'] = request.form['id']
		session['passwd'] = request.form['passwd']
		try:
			if verify(session['id'], session['passwd']):
				return redirect(url_for('personal'))
			else:
				print("no TypeError")
				flash("用户名或密码错误！")
				return render_template('login.html')
		except TypeError:
			print("TypeError")
			flash("用户名或密码错误！")
			return render_template('login.html')

@app.route('/personal/')
def personal():
	try:
		if session['id'] != '':
			database = getConditonal('*','id',session['id'])
			if database != []:
				return render_template('personal_base.html', database = database)
			else:
				flash("请登录！")
				return redirect(url_for('login'))
		else:
			session.pop['id', None]
			#print("session-id = ''")
			return redirect(url_for('login'))
	except KeyError:
		print("TypeError")
		flash("请登录")
		return redirect(url_for('login'))

@app.route('/logout/')
def logout():
	if 'id' in session:
		session.pop('id', None)
	return redirect(url_for('index'))

@app.route('/update/<id>', methods=['GET', 'POST'])
def update(id):
	try:
		if request.method == 'GET':
			print(id)
			return render_template('info_update.html', database=getConditonal('*','id',id),id=id)
		elif request.method == 'POST':
			writeDatabase()
			return redirect(url_for('personal'))
	except KeyError:
		flash("请登录！")
		return redirect(url_for('login'))

@app.route('/search_person/', methods=['GET', 'POST'])
def search_person():
	if request.method == 'POST':
		return render_template('search_person.html', result=grep(request.form['direction'],request.form['content']))
	elif request.method == 'GET':
		return render_template('search_person.html', result=grep('id',''))



######## main ########

if __name__ == '__main__':
	app.run(debug=True)
