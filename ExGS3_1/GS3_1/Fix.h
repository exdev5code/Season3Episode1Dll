#ifndef FIX_H
#define FIX_H

#define ENABLE_SKILL_SUMMON	1
//------------------------------------------------------------------------------
// Character Calculator
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class Fix
{
public:
	Fix(void);
	~Fix(void);
	void Load();

#if(ENABLE_SKILL_SUMMON)
	static int * __thiscall SkillRecallParty(void *This, int a2, int a3);
#endif
};
extern Fix g_Fix;
//------------------------------------------------------------------------
#endif