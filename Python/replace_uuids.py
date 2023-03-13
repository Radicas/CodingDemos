import json
import uuid

with open('file.json', 'r') as f:
    data = json.load(f)

for key in data:
    for item in data[key]:
        item['uuid'] = str(uuid.uuid4())

with open('file.json', 'w') as f:
    json.dump(data, f, indent=2)

