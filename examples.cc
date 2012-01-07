
#include "examples.hh"

MTypeId Locator::id( 0x0, 0x0 );

MTypeId FullOpinionatedLocator::id( 0x0, 0x0 );
MString FullOpinionatedLocator::nodeName( "fullOpinionatedLocator" );
MPxNode::Type FullOpinionatedLocator::nodeType( MPxNode::kLocatorNode );
MString FullOpinionatedLocator::classification( "customClassification" );

MTypeId PartialOpinionatedNode::id( 0x0, 0x0 );
MString PartialOpinionatedNode::nodeName( "partialOpinionatedNode" );

MString Command::commandName( "commandExample" );

