# RFC Zappy
zappy is networking simulation of game of life. Zappy is composed of a server, IA client and GUI client. In the game zappy the world is named trantor is spherical world who live trantorian (IA). The trantorian goal's it to feeds themselves, looking for stones and evolves. All the logical part is ruled by the server and the GUI client is there to watch trantorian. To talk to the server a protocol is set up, and this RFC explain how to implement and use it. There is one protocol for IA client and one for GUI client.

## RFC specification
- **protocol type:** text-based protocol
- **request example:** \<command> <parameters 1> <parameters 2> ... \<parameters n> \<LF>
- **response example:**  \<answer> \<LF>
- **socket type:** TCP
_response will be more detailed later_

## protocol - IA client
all the commands are text-based, each command must end with a line feed. IA protocol commands have time limits called `F` who is the time the server will take to execute another command. Response can be only text-based to inform the IA or response with value, for example and response can be a text like that `[value_1, value_2, ..., value_n]` or `text: value`.

## forward - move up one tile

**description**
> forward command move the trantorian from one tile, the direction is where the trantorian look when the forward command is send

**request** 
>	forward\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>

## right - turn 90 to the right
**description**
> right command change the direction where the trantorian look to 90 degrees to the right

**request** 
>	right\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>

## left - turn 90 to the left
**description**
> left command change the direction where the trantorian look to 90 degrees to the left

**request** 
>	left\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>

## look - look around
**description**
> look command permit to the trantorian to see what is in front of him. At first a trantorian can only see the tile where he is, at each elevation he can see one tile more far and one tile more on each side. the response is a list of tile seen, tile are spearated by comma and object on tile are separated by a space.

**request** 
>	look\<LF>

**time limit**
> 7 / F

**response**
> `[obj_1_tile_1 obj_2_tile_1, obj_1_tile_2 ... obj_n_tile_2, ..., obj_n_tile_n]`\<LF>

## inventory - inventory
**description**
> inventory command permit to the trantorian to see what is in his inventory, inventory list all object possible and say the number the trantorian have in his inventory.

**request** 
>	inventory\<LF>

**time limit**
> 1 / F

**response**
> `[obj1 nbr, obj2 nbr, objn nbr]`\<LF>

## broadcast - broadcast
**description**
> send a message to all trantorian alive, the message send to other trantorian is composed by the orientation (where come from the message) and the `text`, the response to other trantorian is detailled below.

**request** 
>	broadcast `text` \<LF>

**time limit**
> 1 / F

**response**
> ok\<LF>

**response to other client**
> message `K`, `text`\<LF>

## Connect_nbr - number of team unused slots
**description**
> send the number of possible connection for the trantorian team, after a reproduction a trantorian drop an egg an it wait a GUI client to attach before start living

**request** 
>	connect_nbr \<LF>

**time limit**
> _no limit_

**response**
> `value`\<LF>

## fork - create new trantorian
**description**
> create a new player that will wait a GUI client to attach, until no GUI client is attach to the new player, this player is frozen

**request** 
>	fork\<LF>

**time limit**
> 42 / F

**response**
> ok\<LF>

## eject - eject player from this tile
**description**
> eject command push every trantorian on the same tile on the where the player requester look, and destroy all eggs present. player ejected receive another response than the player who eject other, in the response is given a value `K` where it represent the direction where come from the pushed trantorian

**request** 
>	eject\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>
> ko\<LF>

**response to other client**
> eject: `K`

## death - death of the player
**description**
> signal to the IA the death of the player, this command don't need a request it's automatically from the server to the IA

**request** 
>	_No request_

**time limit**
> _No limit_

**response**
> ok\<LF>

## take_object - take an object
**description**
> take an object from the ground on the tile where the trantorian is send ok if he pick up an item and ko if there is no item on the ground

**request** 
>	take_object\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>
> ko\<LF>

## set_object - drop an object
**description**
> drop an object from the inventory to the ground

**request** 
>	take_object\<LF>

**time limit**
> 7 / F

**response**
> ok\<LF>
> ko\<LF>

## incantation - start incantation
**description**
> start an incantation, to start an incantation we need to check if the trantorian have all objects needed on same tile. We check this prerequisite at the start and at the end of the incantation. When an incantation occurred the trantorian is frozen. When an incantation start the message elevation underway is send if it's failed ko is send and if it's succeed current level: `K` is send where `K` is a the trantorian level

**request** 
>	incantation\<LF>

**time limit**
> 300 / F

**response**
> elevation underway
> current level: `K`
> ko\<LF>

## protocol - GUI client
like IA protocol, GUI protocol is text-based protocol but there is no time limits. Some request and response are send with value, there is a `symbol table`. GUI protocol is there to implement a streaming of trantor world, each trantorian is attach by GUI client, that's not mean you can only watch that trantorian you are attach by. When a GUI client is attached to a trantor i can freely see that trantor world's

## symbol table
symbol	| 	Meaning								|
--------|---------------------------------------|
X		|	width or horizontal position		|
Y		|	height or vertical position			|
q0		|	resource 0 (food) quantity			|
q1		|	resource 1 (linemate) quantity		|
q2		|	resource 2 (deraumere) quantity		|
q3		|	resource 3 (sibur) quantity			|
q4		|	resource 4 (mendiane) quantity		|
q5		|	resource 5 (phiras) quantity		|
q6		|	resource 6 (thystame) quantity		|
n		|	player number						|
O		|	orientation: 1(N), 2(E), 3(S), 4(W)	|
L		|	Player or incantation level			|
e		|	egg number							|
T		|	Time unit							|
N		|	Name of the team					|
R		|	incantation result					|
M		|	message								|
i		|	resource number						|

## Client request
there is some request the client can ask and some the server send it to inform the client that an event occurred, ended. We gonna detail the request client can send to the server.

## msz - map size
### description
> command to send at connection of the GUI client to the server. Server response with the `width` and the `height` of the map
### request
> msz\<LF>
### response
> msz `X` `Y`\<LF>

## bct - content of a tile
### description
> this command is useful when a client request to see the content of a certain tile. The client send this request with the position vertical and horizontal of the tile. If the position send by the client is invalid an error message will be send back server response is composed of the horizontal position, vertical position, and resources on the tile
### request
> bct `X`-`Y`\<LF>
### response
> bct `X` `Y` `q0` ... `q6`\<LF>

## mct - content of the map (all the tiles)
### description
> this command is send to update all the map, the server will send multiple response like `bct` command. To know how much response will be send you to calculate the number of the tile. To calculate the `tiles number` you have to a make a quick calculation: `map width` * `map height`.
### request
> mct\<LF>
### response
> bct `X` `Y` `q0` ... `q6`\<LF> * `tiles number`

## ppo - player's position
### description
> client can request a certain player position, the client need to specify the player number
### request
> ppo #`n`\<LF>
### response
> ppo #`n` `X` `Y` `O`\<LF>

## plv- player's level
### description
> client can request player level
### request
> plv #`n`\<LF>
### response
> plv #`n` `L`\<LF>

## plv- player's inventory
### description
> client can request player inventory
### request
> plin#`n`\<LF>
### response
> plv #`n` `X` `Y` `q0` ... `q6`\<LF>

## sgt- time unit request
### description
> _command not understand_
### request
> sgt\<LF>
### response
> sgt `T`\<LF>

## sst - time unit modification
### description
> _command not understand_
### request
> sst `T`\<LF>
### response
> sst `T`\<LF>

## server request
The server send automatically some response to the client, the reason is to keep client informed about event on the trantor world.

## pnw - connection of a new player
### description
> a new trantorian is connected
### response
> pnw #`n` `X` `Y` `O` `L` `N`\<LF>

## pex - expulsion
### description
> signal the GUI if a player gets ex pulsed from a tile and which player by is `id`
### response
> pex #`n`\<LF>

## pbc - broadcast
### description
> signal the GUI if a player broadcast a message, the response is composed by the `player number` and the message
### response
> pbc #`n` `M`\<LF>

## pic - start of an incantation (by the first player)
### description
> signal the GUI if a player start an incantation the response is composed by the `vertical and horizontal position`, `player level` and `player number` of all player who participate at the incantation
### response
> pic `X` `Y` `L` #`n` #`n` ...\<LF>

## pie - end of incantation
### description
> signal the GUI the `result` of he first incantation started, precise the `horizontal and vertical position`
### response
> pie `X` `Y` `R`\<LF>

## pfk - egg laying by the player
### description
> inform the GUI client that a trantorian have `fork` and drop an egg on the ground, the `player number` is specify in the response
### response
> pfk #`n`<LF>

## pdr - resource dropping
### description
> signal the GUI a player drop some resources. In the response the `player number` is specify and the `number of resources` dropped
### response
> pdr #`n` `i`\<LF>

## pgt - resource collecting
### description
> signal the GUI that a player collect resources. In the response the `player number` is specify and the `number of resoruces` collected
### response
> pgt #`n` `i`\<LF>

## pdi - death of a player
### description
> signal the GUI the death of player precised by the `player number``
### response
> pdi #`n`\<LF>

## enw - an egg was laid by a player
### description
> signal the GUI a player laid an egg  on the ground and precise the `egg number`, who is the player by his `player number` and the `horizontal and vertical position`.
### response
> enw #`e` #`n` `X` `Y`\<LF>

## enw - an egg was laid by a player
### description
> signal the GUI a player laid an egg  on the ground and precise the `egg number`, who is the player by his `player number` and the `horizontal and vertical position`.
### response
> enw #`e` #`n` `X` `Y`\<LF>

## ebo - player connecting for an egg
### description
> _need more information about that command_
### response
> ebo #`e`\<LF>              

## edi - death of an egg
### description
> signal the GUI an egg died, specify which egg died by his `egg number`
### response
> edi #`e`\<LF>

## seg - end of game
### description
> signal the end of the game. The game ended when there is no more trantorian on trantor, and precise the last `team` alive
### response
> seg `N`\<LF>

## smg - message from the server
### description
> the server send a `message` to inform the client, it can be a warning message, error message or informative message.
### response
> smg `M`\<LF>

### suc - unknown command
### description
> your command can't be interpreted because it is not implemented in the protocol
### response
> suc\<LF>

## sbp -  command parameter
### description
> client send a valid command but with bad parameters.
### response
> sbp\<LF>