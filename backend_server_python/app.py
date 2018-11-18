import requests
from flask import Flask
from flask_restful import Api, Resource, reqparse

app = Flask(__name__)
api = Api(app)


main_url = 'https://public.api.cryptokitties.co/v1/kitties/'
headers = {'x-api-token': 'IVxxQgD6y0IUCkL1-p6ongyhq94j9z2mKDWVS62pb4c', 'Accept-Charset': 'UTF-8'}


kitties = [
    {
        "user": "1",
        "name": "Genesis",
        "id": 1,
        "action": "up"
    },    
    {
        "user": "2",
        "name": "Riker",
        "id": 42,
        "action": "down"
    }

]

class Info(Resource):
    def get(self,idc):
        kitty = {
            "id":"Action::hit",
            "name":idc
            }
        url = main_url + idc
        r = requests.get(url, headers=headers)
        json_data = r.json()
        return json_data ,200

    def post(self, name):
        return "command not found", 404

    def put(self, name):
        return "command not found", 404

    def delete(self, name):
        return "command not found", 404

class Action(Resource):
    def get(self, user,action):
        for kitty in kitties:
            if(user == kitty["user"]):
                return kitty["action"], 200
        
        return "invalid user" ,400

    def post(self, user,action):

        for kitty in kitties:
            if(user == kitty["user"]):
                kitty["action"] = action
                return "OK", 200
        return "invalid user" ,400

    def put(self, name):
        return "command not found", 404

    def delete(self, name):
        return "command not found", 404
      
api.add_resource(Action, "/action/<string:user>/<string:action>")
api.add_resource(Info, "/info/<string:idc>")

app.run(debug=True)
