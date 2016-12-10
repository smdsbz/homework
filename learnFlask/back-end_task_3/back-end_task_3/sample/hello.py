from flask import Flask, render_template
from flask import redirect, url_for, request, session, make_response
import sqlite3, os

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/form/',methods = ['POST'])
def form():
    db = sqlite3.connect(os.path.join(app.root_path,"test.db"))
    db.execute('insert into test values(?,?)',[request.form['name'], request.form['email']])
    db.commit()
    return render_template('show.html')


@app.route('/show/')
def show():
    db = sqlite3.connect(os.path.join(app.root_path,"test.db"))
    cur = db.execute('select * from test')
    info = cur.fetchall()
    return render_template('info.html', info = info)

if __name__ == '__main__':
    app.run(debug=True)
