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
	database.close()
	return data

def getConditonal(column, conditon, require):
	#print('getConditional(%s,%s,%s) called' % (column,conditon,require))
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select %s from test where %s = '%s'" % (column, conditon, require))
	data = cursor.fetchall()
	#print(data)
	database.close()
	return data

def getAdmin(column, conditon, require):
	#print('getConditional(%s,%s,%s) called' % (column,conditon,require))
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select %s from admin where %s = '%s'" % (column, conditon, require))
	data = cursor.fetchall()
	#print(data)
	database.close()
	return data


def verify(id, passwd):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select passwd from admin where id = '%s'" % id)
	correct = cursor.fetchone()
	database.close()
	#print(correct[0])
	if passwd == correct[0]:
		return 1
	else:
		session.pop('id', None)
		return 0

def updatePerson(id):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# EXTREAMLY-ugly line: write to database
	database.execute("update test set name = '%s', gender = '%s', qq = '%s', tel = '%s', wchat = '%s', emg = '%s', school = '%s', class = '%s', apart = '%s', depart = '%s', grp = '%s', occup = '%s', dateofjoin = '%s' where id = '%s'" % (request.form['name'], request.form['gender'], request.form['qq'], request.form['tel'], request.form['wchat'], request.form['emg'], request.form['school'], request.form['class'], request.form['apart'], request.form['depart'], request.form['group'], request.form['occup'], request.form['dateofjoin'], id))
	database.commit()
	database.close()
	# EXTREAMLY-ugly lines end here

def grep(column, require):
	print('grep(%s,%s) called' % (column,require))
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute("select * from test where %s GLOB '*%s*'" % (column, require))
	data = cursor.fetchall()
	database.close()
	print(data)
	return data

def addPerson():
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# EXTREAMLY-ugly line: write to database
	print("before execute()")
	try:
		print(request.form['emg'])
		database.execute("insert into test (id,name,gender,qq,tel,wchat,emg,school,class,apart,depart,grp,occup,dateofjoin) values ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')" % (request.form['id'], request.form['name'], request.form['gender'], request.form['qq'], request.form['tel'], request.form['wchat'], request.form['emg'], request.form['school'], request.form['class'], request.form['apart'], request.form['depart'], request.form['group'], request.form['occup'], request.form['dateofjoin']))
	except:
		# issue: execute() fail when NULL exist in request.form
		print("addPerson() failed due to invalid request.form element!")
	database.commit()
	database.close()
	# EXTREAMLY-ugly lines end here

def addIssue():
	database = sqlite3.connect(os.path.join(app.root_path,'data.db'))
	try:
		database.execute("insert into issue values ('%s','%s','%s')" % (request.form['id'],request.form['title'],request.form['body']))
	except:
		print((request.form['id'],request.form['title'],request.form['body']))
	database.commit()
	database.close()

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
			database = getAdmin('*','id',session['id'])
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
		session['id']
		if request.method == 'GET':
			print(id)
			return render_template('info_update.html', database=getConditonal('*','id',id),id=id)
		elif request.method == 'POST':
			updatePerson(id)
			return redirect(url_for('personal'))
	except KeyError:
		flash("请登录！")
		return redirect(url_for('login'))

@app.route('/search_person/', methods=['GET', 'POST'])
def search_person():
	try:
		session['id']
		if request.method == 'POST':
			return render_template('search_person.html', result=grep(request.form['direction'],request.form['content']))
		elif request.method == 'GET':
			return render_template('search_person.html', result=grep('id','苟'))
	except KeyError:
		flash("请登录!")
		return redirect(url_for('login'))

@app.route('/entry_person/', methods=['GET', 'POST'])
def entryPerson():
	try:
		print(session['id'])
		if request.method == 'POST':
			addPerson()
			print("addPerson() called")
			return redirect(url_for('personal'))
		elif request.method == 'GET':
			return render_template('info_entry.html')
	except KeyError:
		flash("请登录！")
		return redirect(url_for('login'))

@app.route('/entry_issue/', methods=['GET', 'POST'])
def entryIssue():
	try:
		print(session['id'])
		if request.method == 'POST':
			addIssue()
			print("addIssue() called")
			return redirect(url_for('personal'))
		elif request.method == 'GET':
			return render_template('issue_entry.html')
	except KeyError:
		flash("请登录！")
		return redirect(url_for('login'))


######## main ########

if __name__ == '__main__':
	app.run(debug=True)
