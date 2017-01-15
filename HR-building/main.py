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
	print(data)
	return data

def verify(id, passwd):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select passwd from test where id = ?", [id])
	correct = cursor.fetchone()
	#print(correct[0])
	if passwd == correct[0]:
		return 1
	else:
		return 0

def writeDatabase():	# tested
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# EXTREAMLY-ugly line: write to database
	database.execute('insert into test (name, gender, qq, tel, wchat, emg, school, class, apart, depart, grp, occup, id, dateofjoin) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', [request.form['name'], request.form['gender'], request.form['qq'], request.form['tel'], request.form['wchat'], request.form['emg'], request.form['school'], request.form['class'], request.form['apart'], request.form['depart'], request.form['group'], request.form['occup'], request.form['id'], request.form['dateofjoin']])
	database.commit()
	# EXTREAMLY-ugly lines end here

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
		except TypeError:
			flash("用户名或密码错误，请仔细核对！")
			return render_template('login.html')

@app.route('/personal/')
def personal():
	try:
		return render_template('personal_base.html', database = getConditonal('*','id',session['id']))
	except KeyError:
		flash("请登录再进行操作！")
		return redirect(url_for('index'))

@app.route('/logout/')
def logout():
	if 'id' in session:
		session.pop('id', None)
	return redirect(url_for('index'))

'''
@app.route('/edit_profile/', methods=['GET', 'POST'])
def update():
'''

######## main ########

if __name__ == '__main__':
	app.run(debug=True)
