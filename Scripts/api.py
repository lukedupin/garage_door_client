def api_data():
    return [
      {
        "name": "control",
        "endpoints": [
          { "name": "request_challenge", "resp": "JChallenge", "err": "JErr", "args": []},
          { "name": "download_magic_key", "resp": "JMagicKey", "err": "JErr", "args": ["str challenge"]},
          { "name": "toggle_door", "resp": "JEmpty", "err":  "JErr", "args": ["str challenge_response"] },
          { "name": "door_status", "resp": "JDoorStatus", "err":  "JErr", "args": ["str challenge_response"] },
        ]
      },
    ]
