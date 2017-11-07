#include "main.h"

int main()
{
	char * query;
	char buffer[100];
	s_cgi *cgi;
	FILE *fp;
	FILE *fp2;
	Player player;
	Map map;
	int i, j, len;

	cgi = cgiInit();

	strcpy(buffer,cgiGetValue(cgi,"query"));
	len = strlen(buffer) + 1;
	query = malloc(len * sizeof(char));
	strcpy(query, buffer);

	printf("Content-Type: text/html;charset=us-ascii\n\n");

	player.x = 0;
	player.y = 0;
	player.energy = 0;
	player.money = 0;
	for(i = 0; i < 10; i++) {
		player.inventory[i] = malloc(5 * sizeof(char));
		strcpy(player.inventory[i], "None");
	}

	read_file(&player, &map, fp);

	if(strcmp(query, "N") == 0 || strcmp(query, "S") == 0 || strcmp(query, "E") == 0 || strcmp(query, "W") == 0) {
		move_player(query, &player, &map);
	}

	//temp location for diamond at coordinates (0,0). Fill in these values when location of diamond is placed. 
	int diamondx = 0;
	int diamondy = 0;
	
	
	//If statement to check coordinates that the player has moved into and the coordiantes of the diamonds

	if(map.tiles[diamondx][diamondy].x == player.x && map.tiles[diamondx][diamondy].y == player.y)
	{
			map.tiles[diamondx][diamondy].visibility = 1;
			printf("%s  ", "You have found the diamonds<br>");
	}


	if(map.tiles[diamondx][diamondy].visibility && strcmp(map.tiles[diamondx][diamondy].content, "DIAMOND"))
	{
		resetstate(fp,fp2);
		read_file(&player, &map, fp);
	}

	write_file(&player, &map, fp);

	printf("Player Coordinates: %d, %d<br>", player.x, player.y);
	
	return 0;
}
