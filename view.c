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
	int count = 0;
	int nextseltags, curseltags = selmon->tagset[selmon->seltags];

	if(!(curseltags && !(curseltags & (curseltags - 1)))) return;
	nextseltags = curseltags;
	do{
		count++;
		nextseltags = nextseltags << 1;
		for (c = selmon->clients; c && !visible; c = c->next){
			if (nextseltags & c->tags) {
				visible = 1;
				break;
			}
		}
	} while((nextseltags <= LENGTH(tags))  && (!visible));

	if(!visible)
		nextseltags = 1;
	while(count<9 && (nextseltags < curseltags) && (!visible)){
		count++;
		for (c = selmon->clients; c && !visible; c = c->next){
			if (nextseltags & c->tags) {
				visible = 1;
				break;
			}
		}
		if(visible) break;
		nextseltags = nextseltags << 1;
	}


	if (count < 9) {
		a.i = nextseltags;
		view(&a);
	}
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
