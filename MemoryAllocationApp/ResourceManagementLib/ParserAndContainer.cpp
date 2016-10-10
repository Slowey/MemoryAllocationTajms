#include "ParserAndContainer.h"
#include "ParserAndContainerManager.h"


ParserAndContainer::ParserAndContainer(std::string p_fileEndingToParse)
{
    ParserAndContainerManager::Get().InsertNewParserToList(this, p_fileEndingToParse);
}


ParserAndContainer::~ParserAndContainer()
{
}
