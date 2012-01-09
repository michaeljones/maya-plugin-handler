
#include "examples.hh"

MTypeId Locator::id( 0x80001 );

MTypeId Data::id( 0x80002 );

MTypeId FullOpinionatedLocator::id( 0x80003 );
MString FullOpinionatedLocator::nodeName( "fullOpinionatedLocator" );
MPxNode::Type FullOpinionatedLocator::nodeType( MPxNode::kLocatorNode );
MString FullOpinionatedLocator::classification( "customClassification" );

MTypeId PartialOpinionatedNode::id( 0x80004 );
MString PartialOpinionatedNode::nodeName( "partialOpinionatedNode" );

MString FullOpinionatedCommand::commandName( "fullOpinionatedCommand" );
MString PartialOpinionatedCommand::commandName( "partialOpinionatedCommand" );

MTypeId FullOpinionatedData::id( 0x80005 );
MString FullOpinionatedData::dataName( "fullOpinionatedData" );
MPxData::Type FullOpinionatedData::dataType( MPxData::kGeometryData );

MTypeId PartialOpinionatedData::id( 0x80006 );
MString PartialOpinionatedData::dataName( "partialOpinionatedData" );

