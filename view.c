/** Function to shift the current view to the left/right
 *
 * @param: "arg->i" stores the number of tags to shift right (positive value)
 *          or left (negative value)
 */
void
shiftview(const Arg *arg)
{
	Arg a;
	Client *c;
	unsigned visible = 0;
	int i = arg->i;
	int count = 0;
	int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	do {
		if(i > 0) // left circular shift
			nextseltags = (curseltags << i) | (curseltags >> (LENGTH(tags) - i));

		else // right circular shift
			nextseltags = curseltags >> (- i) | (curseltags << (LENGTH(tags) + i));

                // Check if tag is visible
		for (c = selmon->clients; c && !visible; c = c->next)
			if (nextseltags & c->tags) {
				visible = 1;
				break;
			}
		i += arg->i;
	} while (!visible && ++count < 10);

	if (count < 10) {
		a.i = nextseltags;
		view(&a);
	}
}
void
minOpen(const Arg *arg)
{
	Arg a;
	Client *c;
	int visible[10] = {0,0,0,0,0,0,0,0,0,0};

	for(int i=1;i<10;i++){
		for(c = selmon->clients; c; c = c->next){
			if(i & c->tags){
				visible[i] = 1;
				break;
			}
		}
	}
	for(int i=1;i<10;i++){
		if(!visible[i]){
			a.i = i;
			view(&a);
			break;
		}
	}

}
