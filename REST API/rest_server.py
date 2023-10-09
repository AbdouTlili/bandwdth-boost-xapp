from flask import Flask, request, jsonify, make_response

app = Flask(__name__)

# Your C functions (replace these with actual C function calls)
def c_init():
    return "Initialization complete."

def c_update():
    return "Update complete."

def c_status():
    return "Status: OK"

@app.route('/init', methods=['POST'])
def init():
    try:
        result = c_init()
        return jsonify({'message': result}), 200
    except Exception as e:
        return make_response(jsonify({'error': str(e)}), 500)

@app.route('/update', methods=['POST'])
def update():
    try:
        result = c_update()
        return jsonify({'message': result}), 200
    except Exception as e:
        return make_response(jsonify({'error': str(e)}), 500)

@app.route('/status', methods=['GET'])
def status():
    try:
        result = c_status()
        return jsonify({'message': result}), 200
    except Exception as e:
        return make_response(jsonify({'error': str(e)}), 500)

if __name__ == '__main__':
    app.run(debug=True)