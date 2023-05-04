//---------------------------------------------------------------------------
// precalculating sin and cos table to optimize mathematic operation
//---------------------------------------------------------------------------
void precalculate_tables(void)
{
 int i;

 for(i = 0; i<angolo_360; i++)
 {
  cos_table[i] = cos(RADIAN(i));
  inv_cos_table[i] = 1/cos(RADIAN(i));
  sin_table[i] = sin(RADIAN(i));
  inv_sin_table[i] = 1/sin(RADIAN(i));
  tan_table[i] = tan(RADIAN(i));
  cotan_table[i] = 1/tan(RADIAN(i));

  // for each ray calculate the step to check for a collision with walls (Y axis)
  if ((i >= angolo_0) && (i < angolo_180))
   y_step[i] = fabs(tan(RADIAN(i))) * y_size;
  else y_step[i] = -fabs(tan(RADIAN(i))) * y_size;
  // now do the same for the collision over the X axis
  if ((i >= angolo_90) && (i < angolo_270))
   x_step[i] = -fabs((1/tan(RADIAN(i)))) * x_size;
  else x_step[i] = fabs((1/tan(RADIAN(i)))) * x_size;
 }

 for(i=-angolo_30;i<angolo_30;i++)
  dist_table[i+angolo_30] = 13321 / (float)cos(RADIAN(i));
}

// =============================================================

void draw_scene(long x, long y, long view_angle)
{
 int raggio,
     casting,     // tracks the progress of the X and Y component of the ray
     x_hit_type,  // records the block that was intersected, used to figure
     y_hit_type,  // out which texture to use

     xray=0,        // tracks the progress of a ray looking for Y interesctions
     yray=0,        // tracks the progress of a ray looking for X interesctions
     next_y_cell,   // used to figure out the quadrant of the ray
     next_x_cell,
     x_bound,       // the next vertical and horizontal intersection point
     y_bound,
     x_delta,       // the amount needed to move to get to the next cell
     y_delta,       // position
     cell_x,        // the current cell that the ray is in
     cell_y,
     scale,         // the final scale to draw the "sliver" in
     yi_save,
     xi_save,
     yb_save,
     xb_save;

 long  dist_x,        // the distance of the x and y ray intersections from
       dist_y;        // the viewpoint
  float      xi,            // used to track the x and y intersections
       yi;

 if ((view_angle-=angolo_30) < 0)
  view_angle=angolo_360 + view_angle;

 for (raggio=0; raggio < 240; raggio++)
 {
  if (view_angle >= angolo_0 && view_angle < angolo_180)
  {
   y_bound = (y_size + (y & 0xffc0));
   y_delta = y_size;
   xi = cotan_table[view_angle] * (y_bound - y) + x;
   next_y_cell = 0;
  }
  else {
	y_bound =(int) (y & 0xffc0);
	y_delta = -y_size;
	xi = cotan_table[view_angle] * (y_bound - y) + x;
	next_y_cell = -1;
       }

  if (view_angle < angolo_90 || view_angle >= angolo_270)
  {
   x_bound = (int)(x_size + (x & 0xffc0));
   x_delta = x_size;
   yi = tan_table[view_angle] * (x_bound - x) + y;
   next_x_cell = 0;
  }
  else {
	x_bound = (int)(x & 0xffc0);
	x_delta = -x_size;
	yi = tan_table[view_angle] * (x_bound - x) + y;
	next_x_cell = -1;
       }
  // begin cast

  casting = 2;                // two rays to cast simultaneously
  xray=yray = 0;                // reset intersection flags

  while(casting)
  {
   if (xray != INTERSECTION_FOUND)
   {
    cell_x = (x_bound+next_x_cell) >> 6;
    cell_y = (int) yi >> 6;
    if (cell_x < 0)
        cell_x = 0;
    if (cell_y < 0)
        cell_y = 0;
    if (cell_x > WORLD_X_SIZE)
        cell_x = WORLD_X_SIZE-1;
    if (cell_y > WORLD_Y_SIZE)
        cell_y = WORLD_Y_SIZE-1;
    if ((x_hit_type = mappa[cell_x][cell_y])!= 0)
    {
     dist_x  = (long) ((yi  - y) * inv_sin_table[view_angle]);
     if (dist_x == 0)
      dist_x = 100;
     xray = INTERSECTION_FOUND;
     casting--;
     yi_save = (int)yi;
     xb_save=x_bound;
    }
    else {
 	  yi += y_step[view_angle];
	  x_bound += x_delta;
         }
   }

   if (yray != INTERSECTION_FOUND)
   {
    cell_x = (int)xi >> 6;
    cell_y = ( (y_bound + next_y_cell) >> 6);
    if (cell_x < 0)
        cell_x = 0;
    if (cell_y < 0)
        cell_y = 0;
    if (cell_x > WORLD_X_SIZE)
        cell_x = WORLD_X_SIZE-1;
    if (cell_y > WORLD_Y_SIZE)
        cell_y = WORLD_Y_SIZE-1;
    if ((y_hit_type = mappa[cell_x][cell_y])!=0)
    {
     dist_y  = (long)((xi - x) * inv_cos_table[view_angle]);
     if (dist_y == 0)
      dist_y = 100;
     yray = INTERSECTION_FOUND;
     xi_save = (int)xi;
     yb_save=y_bound;
     casting--;
    }
    else {
	  xi += x_step[view_angle];
	  y_bound += y_delta;
	 }
   }
  }

  if (dist_x < dist_y)
  {
   scale = (int)(dist_table[raggio] / dist_x);

   if (scale > 160) scale=160;
	draw_v_line(raggio, scale, y_hit_type);
  }
  else {
	scale = (int)(dist_table[raggio] / dist_y);

	if (scale > WINDOW_HEIGHT) scale=160;
	draw_v_line(raggio, scale, y_hit_type);
       }

  if (++view_angle>=angolo_360)
  {
   view_angle=0;
  }
 }
}

