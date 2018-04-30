#include <stdio.h>
#include <stdlib.h>

typedef enum {
	 go, stop
} state;

state present_state; //this will keep track of present state globally for the program

typedef enum {
	red_light, green_light
} input;

//forward declarations so we can set func_ptr to them in transitions
void accelerate();
void deccelerate();

typedef void(*func_ptr) ();

typedef struct {
	input i;
	state next;
	func_ptr f;
} transition;

transition go_transition[] = {
	{red_light, stop, deccelerate},
	{green_light, go, accelerate}
};

transition stop_transition[] = {
	{red_light, stop, deccelerate},
	{green_light, go, accelerate}
};

transition * present_state_transitions_ptr[2] = {
	go_transition,
	stop_transition
};

void fsm(state ps, input i) {
	int j;
	for (j = 0; (present_state_transitions_ptr[ps][j].i != i); j++);
	present_state_transitions_ptr[ps][j].f();
	present_state = present_state_transitions_ptr[ps][j].next;
}

void accelerate() {
	if (present_state == go) {
		printf("moving at constant speed\n");
	}
	else {
		printf("accelerating from stop\n");
	}
}

void deccelerate() {
	if (present_state == go) {
		printf("slowing to a stop\n");
	}
	else {
		printf("remaining stationary\n");
	}
}

void main() {
	present_state = go;
	for (int i = 0; i < 30; i++) {
		input a = (int)rand() % 2 % 2 == 0 ? go : stop;
		fsm(present_state, a);
	}
}