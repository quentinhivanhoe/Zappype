# RFC Zappy
zappy is networking simulation of game of life. Zappy is composed of a server, IA and GUI client. In the game zappy the world is named trantor is spherical world who live trantorian (IA). The trantorian goal's it to feeds themselves, looking for stones and evolves. All the logical part is ruled by the server and the GUI client is there to watch trantorian. To talk to the server a protocol is set up, and this RFC explain how to implement and use it. There is to protocol one to IA client and one to GUI client.

## RFC specification
- **protocol type:** text-based protocol
- **request example:** \<command> <parameters 1> <parameters 2> ... \<parameters n> \<LF>
- **response example:**  \<answer> \<LF>
- **socket type:** TCP
_response will be more detailed later_

## commands - IA client
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
> send a message to all trantorian alive, the message send to other trantorian is composed by the orientation (where come from the message) and the text, the response to other trantorian is detailled below.

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