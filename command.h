#ifndef COMMAND_H
#define COMMAND_H

#include "record.h"

class Command: public Record
{
    private:
		commandType command = CMD_NONE;
		int commandOrder = 0;
		operationType operation = OP_NONE;
		conditionType condName = COND_NONE;
		conditionType condPhone = COND_NONE;
		conditionType condGroup = COND_NONE;
		int selectOrder = 0;
		requestStatement statement = REQ_NONE;
		printSort comparator = PS_NONE;

    public:
		Command() = default;
		~Command() = default;

		bool check( Record * tmp);
		bool isOk( Record * tmp, int flagType);
		int like(const char * string, const char * reference);
		int like_default (const char *str_name, const char *str_like);


		const char* getType();
		const char* getCondition(conditionType& type);
		const char* getOperationString();
		const char* getPrintSortChar();

                void clear()
                {
                    command = CMD_NONE;
                    commandOrder = 0;
                    operation = OP_NONE;
                    condName = COND_NONE;
                    condPhone = COND_NONE;
                    condGroup = COND_NONE;
                    selectOrder = 0;
                    statement = REQ_NONE;
		    comparator = PS_NONE;
                    this->setGroup(-1);
                    this->setPhone(-1);

                }

		int getCommandOrder() { return commandOrder; }
		int getSelectOrder() { return selectOrder; }
		int getOrder() { return commandOrder; }
		int getPrintSort() { return comparator;}

		conditionType getNameCondition();
		conditionType getPhoneCondition();
		conditionType getGroupCondition();

		operationType getOperation();
		commandType getCommand();

		bool print(int commandCounter, bool isDebugPrint, FILE* outFile = stdout);
		int parse(const char *str, int *space, char* buff2);
		int parseAddition(const char *str, int *space, char* buff2);
		int parseAdditionOrder(const char *operation, int *space);
		int setCondition(conditionType &current, const char *let, int *spaces);

};

#endif // COMMAND_H
