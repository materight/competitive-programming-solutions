import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161
AWAY_TEAM_ID = 3159

with open("events.json", 'r') as f:
    events = json.load(f)


def dist(a, b):
    return ((a['x'] - b['x']) ** 2 + (a['y'] - b['y'])**2)**0.5


tiri = []

for e in events:
    if e['matchId'] == MATCH_ID and e['eventName'] == 'Shot':
        tiri.append(
            (e['matchPeriod'], e['eventSec'], 100 - e['positions'][0]['x'])
        )

res = sorted(tiri, reverse=True)
f = open("esercizio15.csv", "w")
f.write("tempo;momento;distanza\n")
for t, m, d in res:
    f.write(str(t) + ';' + str(m) + ';' + str(d) + '\n')
f.close()
