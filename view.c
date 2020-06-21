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
	/* int i = arg->i; */
	/* int nextseltags; */
	int occ = 0;
	int curseltags = selmon->tagset[selmon->seltags];
	int curIndex;
	int i;
	int max = 0;
	for(curIndex = 0;curIndex<LENGTH(tags); curIndex++){
		if ((1<<curIndex)&curseltags){
			max = curIndex;
		}
	}
	for (c = selmon->clients; c; c = c->next) {
		occ |= c->tags;
	}
	for(i = 0; i < LENGTH(tags); i++){
		max++;
		if(!(occ & (1 << (max % LENGTH(tags))) || selmon->tagset[selmon->seltags] & (1 << (max % LENGTH(tags)))))
			continue;
		a.ui = 1 << (max % LENGTH(tags));
		view(&a);
		break;
		
	}
	/* do { */
	/* 	if(i > 0) // left circular shift */
	/* 		nextseltags = (curseltags << i) | (curseltags >> (LENGTH(tags) - i)); */

	/* 	else // right circular shift */
	/* 		nextseltags = curseltags >> (- i) | (curseltags << (LENGTH(tags) + i)); */

                /* // Check if tag is visible */
	/* 	for (c = selmon->clients; c && !visible; c = c->next) */
	/* 		if (nextseltags & c->tags) { */
	/* 			visible = 1; */
	/* 			break; */
	/* 		} */
	/* 	i += arg->i; */
	/* } while (!visible && ++count < 10); */

	/* if (count < 10) { */
	/* 	a.i = nextseltags; */
	/* 	view(&a); */
	/* } */
}

void
minOpen(const Arg *arg)
{
	Arg a;
	Client *c;
	int visible[9] = {0,0,0,0,0,0,0,0,0};
	int i;

	for(i=0;i<LENGTH(tags);i++){
		for(c = selmon->clients; c; c = c->next){
			if((1<<i) & c->tags){
				visible[i] = 1;
				break;
			}
		}
	}
	for(i=0;i<LENGTH(tags);i++){
		if(!visible[i]){
			a.i = (1<<i);
			view(&a);
			break;
		}
	}

}
