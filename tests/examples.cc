
#include "examples.hh"

MTypeId Locator::id( 0x8001 );

MTypeId FullOpinionatedLocator::id( 0x80001 );
MString FullOpinionatedLocator::nodeName( "fullOpinionatedLocator" );
MPxNode::Type FullOpinionatedLocator::nodeType( MPxNode::kLocatorNode );
MString FullOpinionatedLocator::classification( "customClassification" );

MTypeId PartialOpinionatedNode::id( 0x80002 );
MString PartialOpinionatedNode::nodeName( "partialOpinionatedNode" );

MString Command::commandName( "opinionatedCommand" );

