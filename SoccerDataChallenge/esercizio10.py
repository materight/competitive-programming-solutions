import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161
AWAY_TEAM_ID = 3159

with open("events.json", 'r') as f:
    events = json.load(f)


def dist(a, b):
    return ((a['x'] - b['x']) ** 2 + (a['y'] - b['y'])**2)**0.5


dist_sum = 0
count = 0

for e in events:
    if e['matchId'] == MATCH_ID and e['eventName'] == 'Shot' and e['teamId'] == HOME_TEAM_ID:
        dist_sum += dist(e['positions'][0], {'x': 100, 'y': 50})
        count += 1

res = round(dist_sum / count, 4)
f = open("esercizio10.csv", "w")
f.write("distanza_media\n")
f.write(str(res) + '\n')
f.close()
