#!/usr/bin/python3
from flask import Flask, render_template
from flask import url_for, session, redirect, make_response
from flask import request, flash
import sqlite3, os

app = Flask(__name__)
app.secret_key = 'DogLeeNation(2B||!2B)-->|'

######## make them short ########

def getAll():	# tested
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select * from test')
	data = cursor.fetchall()
	return data

def getLast(a):
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select * from test where name = \'%s\'' % a)
	data = cursor.fetchone()
	return data

def getName():
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	cursor = database.execute('select name from test')
	data = cursor.fetchall()
	# dumb way to convert data into a list with only one dimension
	names = []
	for each in data:
		for a in each:
			names.append(a)
	return names

def writeDatabase():	# tested
	database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	# ugly line: write to database
	database.execute('insert into test (name, qq, phonenum, address) values(?,?,?,?)', [request.form['name'], request.form['qq'], request.form['phonenum'], request.form['address']])
	database.commit()
	# ugly lines end here


######## route ########

@app.route('/')
def index():
	return '''
	<h3 style="text-align:center">backend_task_3</h3>
	<a href="/make/">/make/</a>
	<a href="/database/">/database/</a>
	'''

@app.route('/make/', methods=['GET'])
def make():
	if request.method == 'GET':
		session['host'] = request.headers['host']
		response = make_response(render_template('make.html', user_host = session['host']))
		response.set_cookie('name', 'you are so great!')
	return response

@app.route('/database/', methods=['GET', 'POST'])
def database():
	if request.method == 'GET':
		return render_template('database.html', database = getAll())
	elif request.method == 'POST':
		# throw away weird posts
		# empty posts
		# start an ugly condition judging
		if request.form['name'] == request.form['qq'] == request.form['phonenum'] == request.form['address'] == '':
		# end condition judging
			flash("Write something before you submit!")
			return render_template('database.html', database = getAll())
		# re-posts
		elif request.form['name'] in getName():
			flash("You are already in the list! Try Ctrl+F to search.")
			return render_template('database.html', database = getAll())
		# illegal input
		elif not request.form['qq'].isdigit():
			flash("QQ numbers should be consist of numbers only!")
			return render_template('database.html', database = getAll())
		elif not request.form['phonenum'].isdigit():
			flash("Phone numbers should be consist of numbers only!")
			return render_template('database.html', database = getAll())
		else:
			writeDatabase()
			return render_template('show.html', each = getLast(request.form['name']))

######## main ########

if __name__  == '__main__':
	app.run(debug=True)
