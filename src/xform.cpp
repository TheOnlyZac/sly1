#include <xform.h>

void SetExitExits(Exit* pexit, EXITS exits)
{
	/* If exits is already the given value, return */
	if (exits == pexit->fKeyed)
	{
		return;
	}

	/* If exits is totals (4) and and exit is not entered (5),
		show level info blot */
	if (pexit->fKeyed == EXITS::Totals)
	{
		if (exits != EXITS::Exiting)
		{
			//levelInfoBlot::unknown()
			goto set_exits;
		}
	}
	else
	{
	set_exits:
		if (exits != EXITS::Exiting)
		{
			pexit->fKeyed = exits;
			goto update_clock;
		}
	}

	//pexit->field_0x2c8 = pexit->field_0x2c8 & 0xfffffcffffffffff | 0x1000000000;
	//IncrementSwHandsOff((SW *)pexit->field_0x14);
	pexit->fKeyed = exits;
update_clock:
	return; //temp
	//pexit->fFollowDefault = g_clock.animation_timer; // todo: implement clock
}