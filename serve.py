from flask import Flask, send_file

app = Flask(__name__)

@app.route("/cat")
def cat():
    return send_file("gs-netcat")

@app.route("/load") 
def load():
    return send_file("loader")

app.run(port=8000)
