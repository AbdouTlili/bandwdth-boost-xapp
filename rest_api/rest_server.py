from flask import Flask 
from markupsafe import escape
from flask import request

app = Flask(__name__)

# - Init (AppID, List of UE (@IP or IMSI), initial_data rate): For a considered 
# application a list of UE that needs an initial data rate)
@app.route('/init',methods=['POST'])
def init():
    if request.method == 'POST':
        try : 
            app_id = request.form['app_id']
            list_of_ue = request.form['list_of_ue']
            list_of_ue = list_of_ue.strip("[]").split(",")
            initial_data_rate = request.form['initial_data_rate']
            return 'AppId {}, list of UEs : {}, initial data rate {}'.format(app_id,list_of_ue,initial_data_rate)
        except KeyError as e : 
            return "Key error, please check that you are using the correct key, refer to the swagger def for more details"
        except Exception as e : 
            print (e.args)
    return "init"

# @app.route('/init',methods=['POST'])
# def init():
#     if request.method == 'POST':
#         return "init 1 "
#     return "init 2 "

# - Status (AppID, UE): It sends back the percentage of decisions accepted by the gNB scheduler.
#  The higher this value, higher the probability that the requested bandwidth for this UE is respected.
#  If this values is close to 0% it means that the requested data rate cannot be respected. 
@app.route('/status/<string:ue_id>',methods=['GET'])
def status(ue_id):
    if request.method == 'GET':
        return 'UE with ID {} status is : --- '.format(ue_id)
    return "status of ue {}".format(escape(ue_id))

# - Update (AppID, list of UE, Delta): Update the requested data rate by Delta. 
# Delta can be negative. We propose to have a step of 1 Mbps.
@app.route('/update',methods=['POST'])
def update():
    if request.method == 'POST':
        try : 
            app_id = request.form['app_id']
            list_of_ue = request.form['list_of_ue']
            list_of_ue = list_of_ue.strip("[]").split(",")
            delta = request.form['delta']
            return 'AppId {}, list of UEs : {}, delta {}'.format(app_id,list_of_ue,delta)
        except KeyError as e : 
            return "Key error, please check that you are using the correct key, refer to the swagger def for more details"
        except Exception as e : 
            print (e.args)
    return "update"

# swagger documentation of the API 
@app.route('/swagger')
def swagger():
    return "swagger"

