def struct_data():
    return [
        {
          "name": "JErr",
          "fields": [
            "bool successful",
            "str reason"
          ]
        },
        {
          "name": "JEmpty",
          "fields": []
        },
        { "name": "JMagicKey",
          "fields": [
              "str magic_key",
          ]
        },
        { "name": "JChallenge",
          "fields": [
              "str challenge",
          ]
        },
        { "name": "JDoorStatus",
          "fields": [
              "bool status",
          ]
        },
        { "name": "JSession",
          "fields": [
              "str magic_key",
          ]
        },
      ]
