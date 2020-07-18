static void		cycle_body(t_visual *ptr, t_coords *coords)
{
	int		h;
	int		w;

	h = ((!coords->x && !coords->y) || (!coords->y && coords->x)) ? 0 : 1;
	while (h < ptr->len)
	{
		w = ((!coords->x && !coords->y) || (coords->y && !coords->x)) ? 0 : 1;
		while (w < ptr->len)
		{
			if (ptr->filler->map[coords->y][coords->x] == 'O')
				put_pixel(ptr, coords->x * ptr->len + w,
				coords->y * ptr->len + h, BLUE);
			else if (ptr->filler->map[coords->y][coords->x] == 'o')
				put_pixel(ptr, coords->x * ptr->len + w,
				coords->y * ptr->len + h, CYAN);
			else if (ptr->filler->map[coords->y][coords->x] == 'X')
				put_pixel(ptr, coords->x * ptr->len + w,
				coords->y * ptr->len + h, RED);
			else if (ptr->filler->map[coords->y][coords->x] == 'x')
				put_pixel(ptr, coords->x * ptr->len + w,
				coords->y * ptr->len + h, ORANGE);
			w++;
		}
		h++;
	}
}

void	color_turn(t_visual *ptr)
{
	t_coords	*coords;

	color_first_image(ptr);
	coords = ptr->filler->player_coords;
	while (coords)
	{
		cycle_body(ptr, coords);
		coords = coords->next;
	}
	coords = ptr->filler->enemy_coords;
	while (coords)
	{
		cycle_body(ptr, coords);
		coords = coords->next;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 11, 31);
}
