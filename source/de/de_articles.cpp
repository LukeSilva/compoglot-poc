#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string de::Articles[14][4][4] = 
{
	{	//Indefinite
		{ "ein"			,"eine"			,"ein"			,"" 				},
		{ "einen"		,"eine"			,"ein"			,"" 				},
		{ "einem"		,"einer"		,"einem"		,"" 				},
		{ "eines"		,"einer"		,"eines"		,"" 				}
	},
	{	//Definite
		{ "der"			,"die"			,"das"			,"die"			},
		{	"den"			,"die"			,"das"			,"die"			},
		{	"dem"			,"der"			,"dem"			,"den" 			},
		{ "des"			,"der"			,"des"			,"der"			}
	},
	{ //No article
		{	""				,""					,""					,""					},
		{	""				,""					,""					,""					},
		{	""				,""					,""					,""					},
		{	""				,""					,""					,""					}
	},
	{	//1st person possessive
		{ "mein"		,"meine"		,"mein"			,"meine"		},
		{	"meinen"	,"meine"		,"mein"			,"meine"		},
		{	"meinem"	,"meiner"		,"meinem"		,"meinen"		},
		{ "meines"	,"meiner"		,"meines"		,"meiner" 	}
	},
	{	//2nd person possessive
		{	"dein"		,"deine"		,"dein"			,"deine"		},
		{	"deinen"	,"deine"		,"dein"			,"deine"		},
		{ "deinem"	,"deiner"		,"deinem"		,"deinen"		},
		{	"deines"	,"deiner"		,"deines"		,"deiner"		}
	},
	{	//3rd person (masculine) possessive
		{ "sein"		,"seine"		,"sein"			,"seine"		},
		{ "seinen"	,"seine"		,"sein"			,"seine"		},
		{ "seinem"	,"seiner"		,"seinem"		,"seinen"		},
		{ "seines"	,"seiner"		,"seines"		,"seiner"		}
	},
	{	//3rd person (feminine) possessive
		{	"ihr"			,"ihre"			,"ihr"			,"ihre"			},
		{	"ihren"		,"ihre"			,"ihr"			,"ihre"			},
		{	"ihrem"		,"ihrer"		,"ihrem"		,"ihren"		},
		{	"ihres"		,"ihrer"		,"ihres"		,"ihrer"		}
	},
	{ //3rd person (neuter) possessive	
		{ "sein"		,"seine"		,"sein"			,"seine"		},
		{ "seinen"	,"seine"		,"sein"			,"seine"		},
		{ "seinem"	,"seiner"		,"seinem"		,"seinen"		},
		{ "seines"	,"seiner"		,"seines"		,"seiner"		}
	},
	{ //1st person plural possessive
		{	"unser"		,"unsere"		,"unser"		,"unsere"		},
		{	"unseren"	,"unsere"		,"unser"		,"unsere"		},
		{	"unserem"	,"unserer"	,"unserem"	,"unseren"	},
		{	"unseres"	,"unserer"	,"unseres"	,"unserer"	},
	},
	{ //2nd person plural possessive
		{	"euer"		,"eure"			,"euer"			,"eure"			},
		{	"euren"		,"eure"			,"euer"			,"eure"			},
		{	"eurem"		,"eure"			,"eurem"		,"euren"		},
		{	"eures"		,"eurer"		,"eures"		,"eurer"		} 
	},
	{ //3rd person plural possessive
		{	"ihr"			,"ihre"			,"ihr"			,"ihre"			},
		{	"ihren"		,"ihre"			,"ihr"			,"ihre"			},
		{	"ihrem"		,"ihrer"		,"ihrem"		,"ihren"		},
		{	"ihres"		,"ihrer"		,"ihres"		,"ihrer"		}
	},
	{ //2nd person formal possessive
		{	"Ihr"			,"Ihre"			,"Ihr"			,"Ihre"			},
		{	"Ihren"		,"Ihre"			,"Ihr"			,"Ihre"			},
		{	"Ihrem"		,"Ihrer"		,"Ihrem"		,"Ihren"		},
		{	"Ihres"		,"Ihrer"		,"Ihres"		,"Ihrer"		} 
	},
	{ //viel
		{	"viel"		,"viel"			,"viel"			,"viele"		},
		{	"viel"		,"viel"			,"viel"			,"viele"		},
		{	"viel"		,"viel"			,"viel"			,"vielen"		},
		{	"viel"		,"viel"			,"viel"			,"vieler"		}
	},
	{ //dies
		{	"dieser"	,"diese"		,"dieses"		,"diese"		},
		{	"diesen"	,"diese"		,"dieses"		,"diese"		},
		{	"diesem"	,"dieser"		,"diesem"		,"diesen"		},
		{	"dieses"	,"dieser"		,"dieses"		,"dieser"		}
	}
};

std::string de::GetArticle(Noun& n)
{
	if (n.ArticleType < -2 || n.ArticleType > 11) return "";
	int GenderID = 0;
	if (GetNounType(n)=='n') GenderID = 2;
	else if (GetNounType(n)=='f') GenderID = 1;
	if (n.IsPlural) GenderID = 3;
	return Articles[n.ArticleType+2][GenderID][n.Data];
}