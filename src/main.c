#include "../include/stuff.h"

#define screenWidth 1280
#define screenHeight 960
#define mapWidth 24
#define mapHeight 24
#define w 1280
#define h 960

typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*img;
	uint32_t		color;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}	t_data;

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void fill_coords(t_data *data, int x1, int y1, int x2, int y2, int color) {
	int x;
	int y;

	x = x1;
	y = y1;
	while (x < x2) { //left to right
		y = y1;
		while (y < y2) { // top to bottom
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		x++;
	}
}

void bres_draw_line(int x1, int y1, int x2, int y2, t_data *data)
{

	// print_coords(data);
	int dx = abs(x2 - x1); //distance x coords
	int dy = abs(y2 - y1); //distance y coords
	int sx = x1 < x2 ? 1 : -1; //slope x
	int sy = y1 < y2 ? 1 : -1; //slope y
	int err = dx - dy; //move vertical or horizontal
	int e2; //error correction * 2
	while (x1 != x2 && y1 != y2) {
		mlx_put_pixel(data->img, x1, y1, blue);
		e2 = err * 2; //err * 2 at the start of next calculation
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void back_and_forth(t_data *data, double moveSpeed, int modifier) {
	float x = data->posX;
	float y = data->posY;
	float dx = data->dirX * (moveSpeed * modifier);
	float dy = data->dirY * (moveSpeed * modifier);
	if(worldMap[(int)(x + dx)][(int)(y)] == 0) {
		data->posX += dx;
	}
	if(worldMap[(int)(x)][(int)(y + dy)] == 0) {
		data->posY += dy;
	}
}

void strafe(t_data *data, double moveSpeed, int modifier) {
	float x = data->posX;
	float y = data->posY;
	float dx = data->dirY * (moveSpeed * modifier);
	float dy = data->dirX * (moveSpeed * modifier);
	if(worldMap[(int)(x + dx)][(int)(y)] == 0) {
		data->posX += dx;
	}
	if(worldMap[(int)(x)][(int)(y - dy)] == 0) {
		data->posY -= dy;
	}
}

void rotation(t_data *data, double rotSpeed, int modifier) {
	double oldDirX = data->dirX;
	rotSpeed = rotSpeed * modifier;
	data->dirX = data->dirX * cos(rotSpeed) - data->dirY * sin(rotSpeed);
	data->dirY = oldDirX * sin(rotSpeed) + data->dirY * cos(rotSpeed);
	double oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(rotSpeed) - data->planeY * sin(rotSpeed);
	data->planeY = oldPlaneX * sin(rotSpeed) + data->planeY * cos(rotSpeed);
}

void loop_hook(void *param) {
	t_data *data;
	data = (t_data *)param;

	// fill_coords(data, 0, 0, screenWidth, screenHeight, white);
	fill_coords(data, 0, 0, screenWidth, screenHeight/2, dark_green);
	fill_coords(data, 0, screenHeight/2, screenWidth, screenHeight, dark_yellow);



	for(int x = 1; x < w-1; x++) {
		double cameraX = 2 * x / (double)w - 1; 
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;
		int mapX = (int)data->posX;
		int mapY = (int)data->posY;
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;
		int hit = 0; 
		int side;
		if(rayDirX < 0)	{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if(rayDirY < 0)	{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}
		while(hit == 0)	{
			
			if(sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			
			if(worldMap[mapX][mapY] > 0) {
				hit = 1;
			}
		}
		if(side == 0) {
			perpWallDist = (sideDistX - deltaDistX);
		}
		else {
			perpWallDist = (sideDistY - deltaDistY);
		}
		int lineHeight = (int)(h / perpWallDist);
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0) {
			drawStart = 0;
		}
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) {
			drawEnd = h - 1;
		}
		switch(worldMap[mapX][mapY]) {
			case 1:
				data->color = red;
				break;
			case 2:
				data->color = green;
				break;
			case 3:
				data->color = blue;
				break;
			case 4:
				data->color = purple;
				break;
			default:
				data->color = yellow;
				break;
		}

		//give x and y sides different brightness
		if(side == 1) {
			data->color = data->color / 2;
		}
		// verLine(x, drawStart, drawEnd, color); // replace with bres draw line
		// printf("x: %d, drawStart: %d, drawEnd: %d\n", x, drawStart, drawEnd);
		// bres_draw_line(x, drawStart, x, drawEnd, data);
		fill_coords(data, x-1, drawStart, x+1, drawEnd, data->color);
		// fill_coords(data, x-1, drawStart, x+1, drawEnd, orange);
	}

	//speed modifiers
	double moveSpeed = 0.1;
	double rotSpeed = 0.05;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE)) {
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) {
		back_and_forth(data, moveSpeed, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
		back_and_forth(data, moveSpeed, -1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) {
		strafe(data, moveSpeed, -1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) {
		strafe(data, moveSpeed, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) {
		//both camera direction and camera plane must be rotated
		rotation(data, rotSpeed, 1);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) {
		//both camera direction and camera plane must be rotated
		rotation(data, rotSpeed, -1);
	}
}

int main(int argc, char **argv) {
	t_data data;

	data.mlx = mlx_init(screenWidth, screenHeight, "flat", true);
	data.img = mlx_new_image(data.mlx, screenWidth, screenHeight);
	data.posX = 22;
	data.posY = 12;
	data.dirX = -1;
	data.dirY = 0;
	data.planeX = 0;
	data.planeY = 0.66;
	
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	fill_coords(&data, 0, 0, screenWidth, screenHeight, white);
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	
	
	mlx_loop(data.mlx);

	mlx_close_window(data.mlx);
	mlx_terminate(data.mlx);
	return 0;

}

