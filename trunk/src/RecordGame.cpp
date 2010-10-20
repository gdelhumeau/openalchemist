// **********************************************************************
//                            OpenAlchemist
//                        ---------------------
//
//  File        : RecordGame.cpp
//  Description : 
//  Author      : Guillaume Delhumeau <guillaume.delhumeau@gmail.com>
//  License     : GNU General Public License 2 or higher
//
// **********************************************************************

#include <ClanLib/core.h>
#include "RecordGame.h"

/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
RecordGame::RecordGame()
{
	_events.reserve(100);
}

/************************************************************************/
/* Place elements                                                       */
/************************************************************************/
void RecordGame::record_place_elements( int piece_1, int piece_1_x, int piece_1_y,
										int piece_2, int piece_2_x, int piece_2_y)
{
	RecordEvent event;
	event.type = RecordEvent::PIECE_PLACED;
	event.piece_1 = piece_1;
	event.piece_1_x = piece_1_x;
	event.piece_1_y = piece_1_y;
	event.piece_2 = piece_2;
	event.piece_2_x = piece_2_x;
	event.piece_2_y = piece_2_y;
	_events.push_back(event);
}

/************************************************************************/
/* Undo                                                                 */
/************************************************************************/
void RecordGame::record_undo()
{
	RecordEvent event;
	event.type = RecordEvent::UNDO;
	_events.push_back(event);
}

/************************************************************************/
/* Export to XML                                                        */
/************************************************************************/
void RecordGame::export_to_xml()
{
	CL_DomDocument xml_document;
	CL_DomElement tag_root = xml_document.create_element("openalchemist-record-game");
	xml_document.append_child(tag_root);
	
	for(std::vector<RecordEvent>::iterator it=_events.begin(); it != _events.end(); ++it)
	{
		const RecordEvent& event = *it;
		switch(event.type)
		{
		case RecordEvent::UNDO:
			{
				CL_DomElement tag_event = xml_document.create_element("undo");
				tag_root.append_child(tag_event);
				break;
			}
		case RecordEvent::PIECE_PLACED:
			{
				CL_DomElement tag_event = xml_document.create_element("pieces-placed");
				tag_root.append_child(tag_event);
				tag_event.set_attribute_int("piece-1",  event.piece_1);
				tag_event.set_attribute_int("piece-1-x",  event.piece_1_x);
				tag_event.set_attribute_int("piece-1-y",  event.piece_1_y);
				tag_event.set_attribute_int("piece-2",  event.piece_2);
				tag_event.set_attribute_int("piece-2-x",  event.piece_2_x);
				tag_event.set_attribute_int("piece-2-y",  event.piece_2_y);
				break;
			}
		}
	}
	
	CL_File file("output.xml", CL_File::create_always, CL_File::access_write);
	xml_document.save(file);
	file.close();

	CL_ZipArchive zip;
	zip.add_file("output.xml", "events.xml");
	zip.save("output.zip");
}