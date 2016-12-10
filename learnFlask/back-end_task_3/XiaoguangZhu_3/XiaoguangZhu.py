#!/usr/bin/python3
from flask import Flask, render_template
from flask import url_for, session, redirect, make_response
from flask import request
import sqlite3,os

app = Flask(__name__)
app.secret_key = 'DogLeeCountry(2B||!2B)1'

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
        response = make_response(render_template('make.html',\
                user_host = session['host']))
        response.set_cookie('name', 'you are so great!')
    return response

@app.route('/database/', methods=['GET', 'POST'])
def database():
	if request.method == 'GET':
	    database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
	    cursor = database.execute('select * from test')
	    data = cursor.fetchall()
	    return render_template('database.html', database = data)
	elif request.method == 'POST':
		database = sqlite3.connect(os.path.join(app.root_path, 'data.db'))
		database.execute('insert into test (name, qq, phonenum, address)\
		values(?,?,?,?)',\
		[request.form['name'], request.form['qq'], request.form['phonenum'],\
		request.form['address']])
		database.commit()
		cursor = database.execute('select * from test order by id desc limit 1')
		data = cursor.fetchone()
		return render_template('show.html', each = data)

######## endroute ########

if __name__  == '__main__':
    app.run(debug=True)
