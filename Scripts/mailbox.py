def mailbox_data():
    return [
        {"section": "System", "endpoints": [
          {"name": "applicationStateChanged", "args": [ "bool online"], "remote": True },
        ]},

        {"section": "Network", "endpoints": [
            {"name": "packetLossDetected", "args": ["int count"] },
            {"name": "networkStatusChanged", "args": [ "bool online" ] },
        ]},

        {"section": "UI", "endpoints": [
            {"name": "uiLoaded", "args": [] },
            {"name": "copyToClipboard", "args": ["str msg"] },
            {"name": "updateSession", "args": ["JSession sess"] },
        ]},

        #QML only messages
        #This is a bit of a failure to isolate mobile, but its probably most logical to set it here
        {"section": "Mobile", "endpoints": [
            {"name": "pushForm", "args": ["str qml_file", "variant args"], "qml_only": True },
            {"name": "replaceForm", "args": ["str qml_file", "variant args"], "qml_only": True },
            {"name": "popForm", "args": [], "qml_only": True },
            {"name": "currentForm", "args": ["str qml_file"], "qml_only": True },

            {"name": "toast", "args": ["str msg", "int duration"], "qml_only": True },
        ]},
]
