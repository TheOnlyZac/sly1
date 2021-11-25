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
			//levelIntoBlot::unknown()
			goto LAB_001f47a8;
		}
	}
	else
	{
		LAB_001f47a8:
		if (exits != EXITS::Exiting)
		{
			pexit->fKeyed = exits;
			goto LAB_001f47e8;
		}
	}

	//pexit->field_0x2c8 = pexit->field_0x2c8 & 0xfffffcffffffffff | 0x1000000000;
	//IncrementSwHandsOff((SW *)pexit->field_0x14);
	pexit->fKeyed = exits;
LAB_001f47e8:
	return; //temp
	//pexit->fFollowDefault = g_clock.animation_timer; // todo: implement clock
}