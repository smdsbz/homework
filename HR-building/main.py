#!usr/bin/python3
from flask import Flask, url_for, redirect, request, session
import sqlite3, os

app = Flask(__name__)

######## functions ########

def getAll():
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select * from test')
	data = cursor.fetchall()
	return data

def getCol(a):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select %s from test' % a)
	data = cursor.fetchall()
	# dumb way to convert data into a list with only one dimension
	names = []
	for each in data:
		for a in each:
			names.append(a)
	return names

def verify(id, passwd):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select ? from test where id = ?', ['passwd', id])
	correct = cursor.fetchone()
	if passwd == correct:
		return 1
	else:
		return 0


def writeDatabase():	# tested
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# ugly line: write to database
	database.execute('insert into test (name, gender, qq, tel, wchat, emg, school, class, apart, depart, group, occup, id, dateofjoin) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)', [request.form['name'], request.form['gender'], request.form['qq'], request.form['tel'], request.form['wchat'], request.form['emg'], request.form['school'], request.form['class'], request.form['apart'], request.form['depart'], request.form['group'], request.form['occup'], request.form['id'], request.form['dateofjoin']])
	database.commit()
	# ugly lines end here

######## route ########

@app.route('/')
def index():
	returen redirect(url_for('/login/'))

@app.route('/login/', methods=['GET', 'POST']):
def login():
	if request.method == 'GET':
		return render_template('login.html');
	elif request.method == 'POST':
		id = request.form['id']
		passwd = request.form['passwd']
		if verify():
			return redirect(url_for('personal', id))
