#!/usr/bin/python3
from flask import Flask, render_template, url_for

SVIP = ['咸鱼', 'juju', 'dalao', '大腿', '油条', '萌新', 'other']

app = Flask(__name__)

@app.route('/')
def index():
	return render_template('index.html',
	index_css = url_for('static', filename='css/index.css'))

@app.route('/step1')
def step1():
	return '<title>CodeMonkey</title> <p>Hello World</p>'

@app.route('/step2')
def step2():
	return render_template('step2.html',
	step2_css = url_for('static', filename='css/step2.css'),
	image = url_for('static', filename='img/MetroLoadin.gif'),
	js = url_for('static', filename='js/step2.js'))

@app.route('/step3', methods=['GET', 'POST'])
def step3_login():
	return '...'

@app.route('/step3/<title>/<name>')
def step3_userpage(title, name):
	something = '<p>'
	for i in SVIP[0:6]:
		if i == title:
			something += '<font color="gold">%s </font>' % i
		else:
			something += '<font>%s </font>' % i
	if title not in SVIP[0:6]:
		something += '<font color="red">other</font>'
	else:
		something += '<font>other</font>'
	something += '</p>'
	return render_template('step3_userpage.html',
	title = title, name = name, something = something)

if __name__ == '__main__':
	app.run(debug=True)
