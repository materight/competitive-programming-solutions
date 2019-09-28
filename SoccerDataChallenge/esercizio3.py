import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161

with open("matches.json", 'r') as f:
    matches = json.load(f)
with open("events.json", 'r') as f:
    events = json.load(f)

player_count = {}

match = list(filter(lambda m: m['wyId'] == MATCH_ID, matches))[0]

players_id = list(map(lambda p: p['playerId'],
                      match['teamsData'][str(HOME_TEAM_ID)]['formation']['lineup']))
for x in match['teamsData'][str(HOME_TEAM_ID)]['formation']['substitutions']:
    players_id.append(x['playerIn'])

for p in players_id:
    player_count[p] = 0


for event in events:
    if(event['matchId'] == MATCH_ID and event['eventName'] == 'Pass' and event['teamId'] == HOME_TEAM_ID):
        player_id = event['playerId']
        player_count[player_id] += 1

res = sorted(list(player_count.items()), key=lambda x: x[0])

f = open("esercizio3.csv", "w")
f.write("playerId;n_pass\n")
for k, v in res:
    f.write(str(k) + ";" + str(v) + "\n")
f.close()
