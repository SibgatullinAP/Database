#include "command.h"

int Command::parseAdditionOrder(const char *operation, int *space)
{
    if ((operation[0] == 'o') && (operation[1] == 'r') && (operation[2] == 'd') && (operation[3] == 'e') && (operation[4] == 'r') && (space[(int) operation[5]]) && (operation[6] == 'b') && (operation[7] == 'y') && (space[(int) operation[8]]))
    {
	operation += 9;
	if(!strcmp(operation, "name;\n") || !strcmp(operation, "name ;\n") || !strcmp(operation, "name ; \n") || !strcmp(operation, "name; \n") )
	{
	    comparator = PS_NAME;
	    statement = CORRECT;
	    return 1;
	}
	if(!strcmp(operation, "phone;\n") || !strcmp(operation, "phone ;\n") || !strcmp(operation, "phone ; \n") || !strcmp(operation, "phone; \n") )
	{
	    comparator = PS_PHONE;
	    statement = CORRECT;
	    return 1;
	}
	if(!strcmp(operation, "group;\n") || !strcmp(operation, "group ;\n") || !strcmp(operation, "group ; \n") || !strcmp(operation, "group; \n") )
	{
	    comparator = PS_GROUP;
	    statement = CORRECT;
	    return 1;
	}
    }
    return 0;
}

int Command::like_default (const char *str_name,const  char *str_like)
{
    int h, g = 0, ret = 1;
    for (h = 0; str_name[h] && str_like[h+g]; h++)
    {
	if (str_like [h+g] == '%') return 1;
	if (str_like [h+g] != '_')
	{
	    if (str_like [h+g] == '\\') g++;
	    if (str_like [h+g] != str_name [h]) { ret = 0; break;}
	}

    }
    if (ret && (str_name[h+g] || str_like[h])) ret = 0;
    if (ret) return 1;
    return 0;
}

int Command::like (const char *str_name,const char *str_like)
{
    const char *p = strchr (str_like, '%');
    if (!p || !*(p+1)) return like_default(str_name, str_like);

    int len_name = strlen(str_name),  A[BUFF_LEN] = {0}, B[BUFF_LEN] = {0}, i;
    A[0] = 1; if (str_like[0] == '%') B[0] = 1;
    int *c, *a=A, *b=B;

    for (i = 0; str_name[i] && str_like[i]; i++)
    {
	if (str_like[i] == '%')
	{
	    for (int h = 1; h < len_name + 1; h++)
	    {
		if (a[h] == 1 || b[h-1] == 1) b[h] = 1;
		a[h] = 0;
	    }
	    a[0] = 0;
	}
	else
	{
	    for (int h = 1; h < len_name + 1; h++)
	    {
		if (a[h-1] == 1 && ( str_like[i] == str_name[h-1] || str_like[i] == '_' ))  b[h] = 1;
		a[h-1] = 0;
	    }
	    a[len_name]=0;
	}
	c = a; a = b; b = c;

    }
    if (str_like[i]) return 0;
    return a[len_name];
}

bool Command::isOk(Record * tmp, int flagType)
{
    bool nameFlag = false;
    bool phoneFlag = false;
    bool groupFlag = false;

    switch(flagType)
    {
        case 1:
	    switch (getNameCondition())
	    {
	        case EQ:
		    if(strcmp(tmp->getName(), getName()) == 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case NE:
		    if(strcmp(tmp->getName(), getName()) != 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LT:
		    if(strcmp(tmp->getName(), getName()) < 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case GT:
		    if(strcmp(tmp->getName(), getName()) > 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LE:
		    if(strcmp(tmp->getName(), getName()) <= 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case GE:
		    if(strcmp(tmp->getName(), getName()) >= 0)
		    {
			nameFlag = true;
		    }
		    break;

	        case LIKE:
		    if(like(tmp->getName(), getName()))
		    {
			nameFlag = true;
		    }
		    break;
	        case COND_NONE: break;
	    }
	    return nameFlag;

        case 2:
	    switch (getPhoneCondition())
	    {
	        case EQ:
		    if(tmp->getPhone() == getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case NE:
		    if(tmp->getPhone() != getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LT:
		    if(tmp->getPhone() < getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case GT:
		    if(tmp->getPhone() > getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LE:
		    if(tmp->getPhone() <= getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case GE:
		    if(tmp->getPhone() >= getPhone())
		    {
			phoneFlag = true;
		    }
		    break;

	        case LIKE: break;
	        case COND_NONE: break;
	    }
	    return phoneFlag;

        case 3:
	    switch (getGroupCondition())
	    {
	        case EQ:
		    if(tmp->getGroup() == getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case NE:
		    if(tmp->getGroup() != getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LT:
		    if(tmp->getGroup() < getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case GT:
		    if(tmp->getGroup() > getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LE:
		    if(tmp->getGroup() <= getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case GE:
		    if(tmp->getGroup() >= getGroup())
		    {
			groupFlag = true;
		    }
		    break;

	        case LIKE: break;
	        case COND_NONE: break;
	    }
	    return groupFlag;

        case 0:
	    return true;
        }

    return false;
}

bool Command::check(Record * tmp)
{

    bool nameFlag = false;
    bool phoneFlag = false;
    bool groupFlag = false;

    switch (getNameCondition())
    {
        case EQ:
	    if(strcmp(tmp->getName(), getName()) == 0)
	    {
		nameFlag = true;
	    }
	    break;

        case NE:
	    if(strcmp(tmp->getName(), getName()) != 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LT:
	    if(strcmp(tmp->getName(), getName()) < 0)
	    {
		nameFlag = true;
	    }
	    break;

        case GT:
	    if(strcmp(tmp->getName(), getName()) > 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LE:
	    if(strcmp(tmp->getName(), getName()) <= 0)
	    {
		nameFlag = true;
	    }
	    break;

        case GE:
	    if(strcmp(tmp->getName(), getName()) >= 0)
	    {
		nameFlag = true;
	    }
	    break;

        case LIKE:
	    if(like(tmp->getName(), getName()))
	    {
		nameFlag = true;
	    }
	    break;
        case COND_NONE: break;
    }

    switch (getPhoneCondition())
    {
        case EQ:
	    if(tmp->getPhone() == getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case NE:
	    if(tmp->getPhone() != getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LT:
	    if(tmp->getPhone() < getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case GT:
	    if(tmp->getPhone() > getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LE:
	    if(tmp->getPhone() <= getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case GE:
	    if(tmp->getPhone() >= getPhone())
	    {
		phoneFlag = true;
	    }
	    break;

        case LIKE: break;
        case COND_NONE: break;
    }

    switch (getGroupCondition())
    {
        case EQ:
	    if(tmp->getGroup() == getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case NE:
	    if(tmp->getGroup() != getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LT:
	    if(tmp->getGroup() < getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case GT:
	    if(tmp->getGroup() > getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LE:
	    if(tmp->getGroup() <= getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case GE:
	    if(tmp->getGroup() >= getGroup())
	    {
		groupFlag = true;
	    }
	    break;

        case LIKE: break;
        case COND_NONE: break;
    }

    bool result = false;

    switch (getOperation())
    {
        case OR:
	    if(getNameCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = nameFlag || phoneFlag;
	    }
	    if(getNameCondition() != COND_NONE && getGroupCondition() != COND_NONE)
	    {
		result = nameFlag || groupFlag;
	    }
	    if(getGroupCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = groupFlag || phoneFlag;
	    }
	    break;

        case AND:
	    if(getNameCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = nameFlag && phoneFlag;
	    }
	    if(getNameCondition() != COND_NONE && getGroupCondition() != COND_NONE)
	    {
		result = nameFlag && groupFlag;
	    }
	    if(getGroupCondition() != COND_NONE && getPhoneCondition() != COND_NONE)
	    {
		result = groupFlag && phoneFlag;
	    }
	    break;

        case OP_NONE:
	    if(getNameCondition() != COND_NONE)
	    {
		result = nameFlag;
	    }
	    if(getPhoneCondition() != COND_NONE)
	    {
		result = phoneFlag;
	    }
	    if(getGroupCondition() != COND_NONE)
	    {
		result = groupFlag;
	    }
	    break;
    }
    return result;
}

bool Command::print(int commandCounter, bool isDebugPrint, FILE* outFile)
{
    if (isDebugPrint)
    {
	if(commandCounter == 0)
	{
	    fprintf(outFile, "\t|     №    |     Name     |   Phone   | Group | Order |   Type   | Condition_Name | Condition_Phone | Condition_Group | Operation |Comparator for sorting|\n"
	                      "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
	fprintf(outFile, "\t|%10d|%14s|%11d|%7d|%7d|%10s|%16s|%17s|%17s|%11s|%11s|\n",
	        commandCounter, getName(), getPhone(), getGroup(), getOrder(), getType(),
	            getCondition(condName), getCondition(condPhone), getCondition(condGroup), getOperationString(), getPrintSortChar());
	return 1;
    }
    else
    {
	if ((command == SELECT) || (command == DELETE))
	{
	    if (commandOrder == 1)
	    {
		if (condName)
		{
		    fprintf(outFile, "name %s %s;\n", getCondition(condName), getName());
		}
		if (condPhone)
		{
		    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
		}
		if (condGroup)
		{
		    fprintf(outFile, "group %s %d;\n", getCondition(condGroup), getGroup());
		}
		return true;
	    }
	    else
	    {
		if (commandOrder == 2)
		{
		    if (condName)
		    {
			fprintf(outFile, "name %s %s %s ", getCondition(condName), getName(), getOperationString());
			if (condPhone)
			{
			    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
			}
			if (condGroup)
			{
			    fprintf(outFile, "group %s %d;\n", getCondition(condGroup), getGroup());
			}
			return true;
		    }
		    else
		    {
			fprintf(outFile, "phone %s %d %s group %s %d;\n", getCondition(condPhone), getPhone(), getOperationString(), getCondition(condGroup), getGroup());
			return true;
		    }
		}
		else
		{
		    if (condGroup)
		    {
			fprintf(outFile, "group %s %d %s ", getCondition(condGroup), getGroup(), getOperationString());
			if (condName)
			{
			    fprintf(outFile, "name %s %s;\n", getCondition(condName), getName());
			}
			if (condPhone)
			{
			    fprintf(outFile, "phone %s %d;\n", getCondition(condPhone), getPhone());
			}
			return true;
		    }
		    else
		    {
			fprintf(outFile, "phone %s %d %s name %s %s;", getCondition(condPhone), getPhone(), getOperationString(), getCondition(condName), getName());
			return true;
		    }
		}
	    }
	}
	if ((command == QUIT) || (command == STOP))
	{
	        fprintf(outFile, "%s;\n", getType());
		return true;
	}
	if (command == INSERT)
	{
	        fprintf(outFile, "%s (%s, %d, %d);\n", getType(), getName(), getPhone(), getGroup());
		return true;
	}
	fprintf(outFile, "\n");
	return false;
    }
}

const char* Command::getPrintSortChar()
{
    switch (comparator)
    {
	case PS_NONE:
	    return "none";

	case PS_NAME:
	    return "name";

	case PS_PHONE:
	    return "phone";

	case PS_GROUP:
	    return "group";
    }
    return "none" ;
}

commandType Command::getCommand()
{
    return command;
}

const char* Command::getType()
{
    switch(command)
    {
        case CMD_NONE:
	        return "";
        case QUIT:
	        return "quit";
        case STOP:
	        return "stop";
        case SELECT:
	        return "select";
        case INSERT:
	        return "insert";
	case DELETE:
	        return "delete";
    }
    return "";
}

conditionType Command::getNameCondition()
{
    return condName;
}
conditionType Command::getPhoneCondition()
{
    return condPhone;
}
conditionType Command::getGroupCondition()
{
    return condGroup;
}

operationType Command::getOperation()
{
    return operation;
}

const char* Command::getCondition(conditionType& type)
{
    switch(type)
    {
        case COND_NONE:
	        return "";
        case EQ:
	        return "=";
        case NE:
	        return "<>";
        case LT:
	        return "<";
        case GT:
	        return ">";
        case LE:
	        return "<=";
        case GE:
	        return ">=";
        case LIKE:
	        return "like";
    }
    return "";
}

const char* Command::getOperationString()
{
    switch(operation)
    {
        case OP_NONE:
	        return "";
        case AND:
	        return "and";
        case OR:
	        return "or";
    }
    return "";
}


int Command::parse(const char *string, int *spaces, char *buff)
{
    int i = 0, j = 0;
    const char *instruction,  *f = string;
    statement = INCORRECT;

    while(spaces[(int) f[i]])
    {
	i++;
    }
    if (!f[i])
    {
	return 0;
    }
    instruction = f + i;

    if ((instruction[0] == 's') && (instruction[1] == 'e') && (instruction[2] == 'l') && (instruction[3] == 'e') && (instruction[4] == 'c') && (instruction[5] == 't') && (spaces[(int) instruction[6]]))
    {
	command = SELECT; f = instruction + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	instruction = f + i;
	                                                                                                                                                                                                                                        //сценарий аргументов selecet
	                                                                                                                                                                                                                                        //тут можно реализовать возможность иметь 1,2 аргументов вывода select
	                                                                                                                                                                                                                                        //также, как и в AND и OR
	if (instruction[0] == '*')
	{
	    selectOrder = 90; f = instruction + 1; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] == ';')
	    {
		selectOrder = 100;
		statement = CORRECT;
		return 1;
	    }
	    instruction = f + i;
	    return parseAddition(instruction, spaces, buff);
	}
	else
	{
	    return 0;
	}
    }

    if ((instruction[0] == 's') && (instruction[1] == 't') && (instruction[2] == 'o') && (instruction[3] == 'p'))
    {
	command = STOP; f = instruction + 4; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
	else
	{
	    return 0;
	}
    }
    if ((instruction[0] == 'd') && (instruction[1] == 'e') && (instruction[2] == 'l') && (instruction[3] == 'e') && (instruction[4] == 't') && (instruction[5] == 'e'))
    {
	command =DELETE; f = instruction + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
	instruction = f + i;
	return parseAddition(instruction, spaces, buff);
    }

    if ((instruction[0] == 'q') && (instruction[1] == 'u') && (instruction[2] == 'i') && (instruction[3] == 't'))
    {
	command = QUIT; f = instruction + 4; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ';')
	{
	    statement = CORRECT;
	    return 1;
	}
    }

    if ((instruction[0] == 'i') && (instruction[1] == 'n') && (instruction[2] == 's') && (instruction[3] == 'e') && (instruction[4] == 'r') && (instruction[5] == 't') && (spaces[(int) instruction[6]]))
    {
	command = INSERT; f = instruction + 6; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] != '(')
	{
	    return 0;
	}

	i++;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}


	for (instruction = f + i, j = 0; instruction[j] && (!spaces[(int) instruction[j]]) && (instruction[j] != ','); j++)
	{
	    buff[j] = instruction[j];
	}
	buff[j] = 0;

	if (!instruction[j])
	{
	    return 0;
	}
	if (instruction[j] == ',')
	{
	    j++;
	}
	setName(buff);

	f = instruction + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ',')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	}

	for (instruction = f + i, j = 0; instruction[j] && (!spaces[(int) instruction[j]]) && (instruction[j] != ','); j++)
	{
	    buff[j] = instruction[j];
	}
	buff[j] = 0;

	if (!instruction[j])
	{
	    return 0;
	}
	if (instruction[j] == ',')
	{
	    j++;
	}
	if (!setPhone(buff))
	{
	    return 0;
	}
	f = instruction + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ',')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	}
	for (instruction = f + i, j = 0; instruction[j] && (!spaces[(int) instruction[j]]) && (instruction[j] != ')'); j++)
	{
	    buff[j] = instruction[j];
	}
	buff[j] = 0;

	if (!instruction[j])
	{
	    return 0;
	}

	if (!setGroup(buff))
	{
	    return 0;
	}

	if (instruction[j] == ')')
	{
	    j++;
	    f = instruction + j; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] ==';')
	    {
		statement = CORRECT;
		return 1;
	    }
	    else
	    {
		return 0;
	    }
	}

	f = instruction + j; i = 0;

	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	if (f[i] == ')')
	{
	    i++;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] ==';')
	    {
		statement = CORRECT;
		return 1;
	    }
	    else
	    {
		return 0;
	    }
	}
    }

    return 0;
}

int Command::parseAddition(const char *instruction, int *spaces, char *buff)
{
    int i = 0, j = 0;
    const char *f;
    if ((instruction[0] == 'w') && (instruction[1] == 'h') && (instruction[2] == 'e') && (instruction[3] == 'r') && (instruction[4] == 'e') && (spaces[(int) instruction[5]]))
    {
	f = instruction + 5; i = 0;
	while(f[i] && spaces[(int) f[i]])
	{
	    i++;
	}
	if (!f[i])
	{
	    return 0;
	}
	instruction = f + i;
	                                                                                                                                                                                                                                //первый name
	if ((instruction[0] == 'n') && (instruction[1] == 'a') && (instruction[2] == 'm') && (instruction[3] == 'e') && (spaces[(int) instruction[4]]))
	{
	    f = instruction + 4; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    instruction = f + i;

	    if (!(j = setCondition(condName, instruction, spaces)))
	    {
		return 0;
	    }

	    f = instruction + j; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i] || f[i] == ';')
	    {
		return 0;
	    }
	    instruction = f + i;

	    j = 0;
	    while (!spaces[(int) instruction[j]] && instruction[j] != ';')
	    {
		buff[j] = instruction[j];
		j++;
	    }
	    buff[j] = 0;
	    setName(buff);

	    f = instruction + j; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    if (f[i] == ';')
	    {
		commandOrder = 1;
		statement = CORRECT;
		return 1;
	    }
	    instruction = f + i;

	    if ((instruction[0] == 'a') && (instruction[1] == 'n') && (instruction[2] == 'd') && (spaces[(int) instruction[3]]))
	    {
		operation = AND;
		j = 3;
	    }
	    else
	    {
		if ((instruction[0] == 'o') && (instruction[1] == 'r') && (spaces[(int) instruction[2]]))
		{
		    operation = OR;
		    j = 2;
		}
		else
		{
		    commandOrder = 1;
		    return parseAdditionOrder(instruction,spaces);
		}
	    }
	    f = instruction + j; i = 0;
	    while(f[i] && spaces[(int) f[i]])
	    {
		i++;
	    }
	    if (!f[i])
	    {
		return 0;
	    }
	    instruction = f + i;


	    if ((instruction[0] == 'p') && (instruction[1] == 'h') && (instruction[2] == 'o') && (instruction[3] == 'n') && (instruction[4] == 'e') && (spaces[(int) instruction[5]]))
	    {
		f = instruction + 5; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		instruction = f + i;

		if (!(j = setCondition(condPhone, instruction, spaces)))
		{
		    return 0;
		}

		f = instruction + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i] || f[i] == ';')
		{
		    return 0;
		}
		instruction = f + i;

		j = 0;
		while (!spaces[(int) instruction[j]] && instruction[j] != ';')
		{
		    buff[j] = instruction[j];
		    j++;
		}
		buff[j] = 0;
		if (!setPhone(buff))
		{
		    return 0;
		}

		f = instruction + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		if (f[i] == ';')
		{
		    commandOrder = 2;
		    statement = CORRECT;
		    return 1;
		}
		else
		{
		    commandOrder = 2;
		    return parseAdditionOrder(f + 1,spaces);
		}
	    }
	    else
	    {
		if ((instruction[0] == 'g') && (instruction[1] == 'r') && (instruction[2] == 'o') && (instruction[3] == 'u') && (instruction[4] == 'p') && (spaces[(int) instruction[5]]))
		{
		    f = instruction + 5; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    instruction = f + i;

		    if (!(j = setCondition(condGroup, instruction, spaces)))
		    {
			return 0;
		    }

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i] || f[i] == ';')
		    {
			return 0;
		    }
		    instruction = f + i;

		    j = 0;
		    while (!spaces[(int) instruction[j]] && instruction[j] != ';')
		    {
			buff[j] = instruction[j];
			j++;
		    }
		    buff[j] = 0;
		    if (!setGroup(buff))
		    {
			return 0;
		    }

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    if (f[i] == ';')
		    {
			commandOrder = 2;
			statement = CORRECT;
			return 1;
		    }
		    else
		    {
			commandOrder = 2;
			return parseAdditionOrder(f + 1,spaces);
		    }
		}
		else
		{
		    return 0;
		}
	    }
	}
	else
	{																															//первый phone
	    if ((instruction[0] == 'p') && (instruction[1] == 'h') && (instruction[2] == 'o') && (instruction[3] == 'n') && (instruction[4] == 'e') && (spaces[(int) instruction[5]]))
	    {
		f = instruction + 5; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		instruction = f + i;

		if (!(j = setCondition(condPhone, instruction, spaces)))
		{
		    return 0;
		}

		f = instruction + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i] || f[i] == ';')
		{
		    return 0;
		}
		instruction = f + i;

		j = 0;
		while (!spaces[(int) instruction[j]] && instruction[j] != ';')
		{
		    buff[j] = instruction[j];
		    j++;
		}
		buff[j] = 0;
		if (!setPhone(buff))
		{
		    return 0;
		}

		f = instruction + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		if (f[i] == ';')
		{
		    commandOrder = 1;
		    statement = CORRECT;
		    return 1;
		}
		instruction = f + i;

		if ((instruction[0] == 'a') && (instruction[1] == 'n') && (instruction[2] == 'd') && (spaces[(int) instruction[3]]))
		{
		    operation = AND;
		    j = 3;
		}
		else
		{
		    if ((instruction[0] == 'o') && (instruction[1] == 'r') && (spaces[(int) instruction[2]]))
		    {
			operation = OR;
			j = 2;
		    }
		    else
		    {
			commandOrder = 1;
			return parseAdditionOrder(instruction,spaces);
		    }
		}
		f = instruction + j; i = 0;
		while(f[i] && spaces[(int) f[i]])
		{
		    i++;
		}
		if (!f[i])
		{
		    return 0;
		}
		instruction = f + i;

		                                                                                                                                                                                                                                                                //PN
		if ((instruction[0] == 'n') && (instruction[1] == 'a') && (instruction[2] == 'm') && (instruction[3] == 'e') && (spaces[(int) instruction[4]]))
		{
		    f = instruction + 4; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    instruction = f + i;

		    if (!(j = setCondition(condName, instruction, spaces)))
		    {
			return 0;
		    }

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i] || f[i] == ';')
		    {
			return 0;
		    }
		    instruction = f + i;

		    j = 0;
		    while (!spaces[(int) instruction[j]] && instruction[j] != ';')
		    {
			buff[j] = instruction[j];
			j++;
		    }
		    buff[j] = 0;
		    setName(buff);

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    if (f[i] == ';')
		    {
			commandOrder = 3;
			statement = CORRECT;
			return 1;
		    }
		    else
		    {
			commandOrder = 3;
			return parseAdditionOrder(f + 1,spaces);
		    }
		}
		else
		{																																		    //PG
		    if ((instruction[0] == 'g') && (instruction[1] == 'r') && (instruction[2] == 'o') && (instruction[3] == 'u') && (instruction[4] == 'p') && (spaces[(int) instruction[5]]))
		    {
			f = instruction + 5; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			instruction = f + i;

			if (!(j = setCondition(condGroup, instruction, spaces)))
			{
			    return 0;
			}

			f = instruction + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i] || f[i] == ';')
			{
			    return 0;
			}

			instruction = f + i;

			j = 0;
			while (!spaces[(int) instruction[j]] && instruction[j] != ';')
			{
			    buff[j] = instruction[j];
			    j++;
			}
			buff[j] = 0;
			if (!setGroup(buff))
			{
			    return 0;
			}

			f = instruction + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			if (f[i] == ';')
			{
			    commandOrder = 2;
			    statement = CORRECT;
			    return 1;
			}
			else
			{
			    commandOrder = 2;
			    return parseAdditionOrder(f + 1,spaces);
			}
		    }
		    else
		    {
			return 0;
		    }
		}
	    }
	    else
	    {
		                                                                                                                                                                                                                                                            //group первый
		if ((instruction[0] == 'g') && (instruction[1] == 'r') && (instruction[2] == 'o') && (instruction[3] == 'u') && (instruction[4] == 'p') && (spaces[(int) instruction[5]]))
		{
		    f = instruction + 5; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    instruction = f + i;

		    if (!(j = setCondition(condGroup, instruction, spaces)))
		    {
			return 0;
		    }

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i] || f[i] == ';')
		    {
			return 0;
		    }
		    instruction = f + i;

		    j = 0;
		    while (!spaces[(int) instruction[j]] && instruction[j] != ';')
		    {
			buff[j] = instruction[j];
			j++;
		    }
		    buff[j] = 0;
		    if (!setGroup(buff))
		    {
			return 0;
		    }

		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    if (f[i] == ';')
		    {
			commandOrder = 1;
			statement = CORRECT;
			return 1;
		    }
		    instruction = f + i;

		    if ((instruction[0] == 'a') && (instruction[1] == 'n') && (instruction[2] == 'd') && (spaces[(int) instruction[3]]))
		    {
			operation = AND;
			j = 3;
		    }
		    else
		    {
			if ((instruction[0] == 'o') && (instruction[1] == 'r') && (spaces[(int) instruction[2]]))
			{
			    operation = OR;
			    j = 2;
			}
			else
			{
			    commandOrder = 1;
			    return parseAdditionOrder(instruction,spaces);
			}
		    }
		    f = instruction + j; i = 0;
		    while(f[i] && spaces[(int) f[i]])
		    {
			i++;
		    }
		    if (!f[i])
		    {
			return 0;
		    }
		    instruction = f + i;

		                                                                                                                                                                                                                                    //GN

		    if ((instruction[0] == 'n') && (instruction[1] == 'a') && (instruction[2] == 'm') && (instruction[3] == 'e') && (spaces[(int) instruction[4]]))
		    {
			f = instruction + 4; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			instruction = f + i;

			if (!(j = setCondition(condName, instruction, spaces)))
			{
			    return 0;
			}


			f = instruction + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i] || f[i] == ';')
			{
			    return 0;
			}
			instruction = f + i;

			j = 0;
			while (!spaces[(int) instruction[j]] && instruction[j] != ';')
			{
			    buff[j] = instruction[j];
			    j++;
			}
			buff[j] = 0;
			setName(buff);

			f = instruction + j; i = 0;
			while(f[i] && spaces[(int) f[i]])
			{
			    i++;
			}
			if (!f[i])
			{
			    return 0;
			}
			if (f[i] == ';')
			{
			    commandOrder = 3;
			    statement = CORRECT;
			    return 1;
			}
			else
			{
			    commandOrder = 3;
			    return parseAdditionOrder(instruction + 1,spaces);
			}
		    }
		                                                                                                                                                                                                                                    //GP
		    else
		    {
			if ((instruction[0] == 'p') && (instruction[1] == 'h') && (instruction[2] == 'o') && (instruction[3] == 'n') && (instruction[4] == 'e') && (spaces[(int) instruction[5]]))
			{
			    f = instruction + 5; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i])
			    {
				return 0;
			    }
			    instruction = f + i;

			    if (!(j = setCondition(condPhone, instruction, spaces)))
			    {
				return 0;
			    }

			    f = instruction + j; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i] || f[i] == ';')
			    {
				return 0;
			    }
			    instruction = f + i;

			    j = 0;
			    while (!spaces[(int) instruction[j]] && instruction[j] != ';')
			    {
				buff[j] = instruction[j];
				j++;
			    }
			    buff[j] = 0;
			    if (!setPhone(buff))
			    {
				return 0;
			    }

			    f = instruction + j; i = 0;
			    while(f[i] && spaces[(int) f[i]])
			    {
				i++;
			    }
			    if (!f[i])
			    {
				return 0;
			    }
			    if (f[i] == ';')
			    {
				commandOrder = 3;
				statement = CORRECT;
				return 1;
			    }
			    else
			    {
				commandOrder = 3;
				return parseAdditionOrder(f + 1, spaces);
			    }
			}
			else
			{
			    return 0;
			}
		    }
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    else
    {
	return 0;
    }
}

int Command::setCondition(conditionType &current, const char *instruction, int *spaces)
{
    if (instruction[0] == '<')
    {
	if (instruction[1] == '>')
	{
	    current = NE;
	    return 2;
	}
	else
	{
	    if (instruction[1] == '=')
	    {
		current = LE;
		return 2;
	    }
	    else
	    {
		if (spaces[(int) instruction[1]])
		{
		    current = LT;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    else
    {
	if (instruction[0] == '>')
	{
	    if (instruction[1] == '=')
	    {
		current = GE;
		return 2;
	    }
	    else
	    {
		if (spaces[(int) instruction[1]])
		{
		    current = GT;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	}
	else
	{
	    if (instruction[0] == '=')
	    {
		if (spaces[(int) instruction[1]])
		{
		    current = EQ;
		    return 1;
		}
		else
		{
		    return 0;
		}
	    }
	    else
	    {
		if ((instruction[0] == 'l') && (instruction[1] == 'i') && (instruction[2] == 'k') && (instruction[3] == 'e') && (spaces[(int) instruction[4]]))
		{
		    current = LIKE;
		    return 4;
		}
		else
		{
		    return 0;
		}
	    }
	}
    }
    return 1;
}
