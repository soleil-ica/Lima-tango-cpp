/*----- PROTECTED REGION ID(TeledynePIClass.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TeledynePIClass.cpp
//
// description : C++ source for the TeledynePIClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the TeledynePI once per process.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <TeledynePIClass.h>

/*----- PROTECTED REGION END -----*/	//	TeledynePIClass.cpp

//-------------------------------------------------------------------
/**
 *	Create TeledynePIClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_TeledynePI_class(const char *name) {
		return TeledynePI_ns::TeledynePIClass::init(name);
	}
}

namespace TeledynePI_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
TeledynePIClass *TeledynePIClass::_instance = NULL;

//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::TeledynePIClass(string &s)
 * description : 	constructor for the TeledynePIClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
TeledynePIClass::TeledynePIClass(string &s):Tango::DeviceClass(s)
{
	cout2 << "Entering TeledynePIClass constructor" << endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(TeledynePIClass::constructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::constructor

	cout2 << "Leaving TeledynePIClass constructor" << endl;
}

//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::~TeledynePIClass()
 * description : 	destructor for the TeledynePIClass
 */
//--------------------------------------------------------
TeledynePIClass::~TeledynePIClass()
{
	/*----- PROTECTED REGION ID(TeledynePIClass::destructor) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
TeledynePIClass *TeledynePIClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new TeledynePIClass(s);
		}
		catch (bad_alloc &)
		{
			throw;
		}
	}
	return _instance;
}

//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
TeledynePIClass *TeledynePIClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}



//===================================================================
//	Command execution method calls
//===================================================================

//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::get_class_property()
 *	Description : Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum TeledynePIClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::get_default_device_property()
 *	Description : Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum TeledynePIClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::get_default_class_property()
 *	Description : Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum TeledynePIClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::set_default_property()
 *	Description : Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void TeledynePIClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;
	vector<string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
	prop_name = "TemperatureTargetAtInit";
	prop_desc = "Define the target temperature to be used at device initialization";
	prop_def  = "-60";
	vect_data.clear();
	vect_data.push_back("-60");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);
}

//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::write_class_property()
 *	Description : Set class description fields as property in database
 */
//--------------------------------------------------------
void TeledynePIClass::write_class_property()
{
	//	First time, check if database used
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("");
	description << str_desc;
	data.push_back(description);

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("TANGO_BASE_CLASS");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	get_db_class()->put_property(data);
}

//===================================================================
//	Factory methods
//===================================================================

//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::device_factory()
 *	Description : Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void TeledynePIClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
	/*----- PROTECTED REGION ID(TeledynePIClass::device_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::device_factory_before

	//	Create devices and add it into the device list
	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
		device_list.push_back(new TeledynePI(this, (*devlist_ptr)[i]));
	}

	//	Manage dynamic attributes if any
	erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

	//	Export devices to the outside world
	for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
	{
		//	Add dynamic attributes if any
		TeledynePI *dev = static_cast<TeledynePI *>(device_list[device_list.size()-i]);
		dev->add_dynamic_attributes();

		//	Check before if database used.
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(dev);
		else
			export_device(dev, dev->get_name().c_str());
	}

	/*----- PROTECTED REGION ID(TeledynePIClass::device_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::attribute_factory()
 *	Description : Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void TeledynePIClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(TeledynePIClass::attribute_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::attribute_factory_before
	//	Attribute : temperature
	temperatureAttrib	*temperature = new temperatureAttrib();
	Tango::UserDefaultAttrProp	temperature_prop;
	temperature_prop.set_description("The current temperature  (Degree Celsius)");
	//	label	not set for temperature
	temperature_prop.set_unit("deg C");
	//	standard_unit	not set for temperature
	//	display_unit	not set for temperature
	temperature_prop.set_format("%6.2f");
	//	max_value	not set for temperature
	//	min_value	not set for temperature
	//	max_alarm	not set for temperature
	//	min_alarm	not set for temperature
	//	max_warning	not set for temperature
	//	min_warning	not set for temperature
	//	delta_t	not set for temperature
	//	delta_val	not set for temperature
	
	temperature->set_default_properties(temperature_prop);
	//	Not Polled
	temperature->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(temperature);

	//	Attribute : temperatureTarget
	temperatureTargetAttrib	*temperaturetarget = new temperatureTargetAttrib();
	Tango::UserDefaultAttrProp	temperaturetarget_prop;
	temperaturetarget_prop.set_description("Define the Temperature target of the detector (in deg Celsius)");
	//	label	not set for temperatureTarget
	temperaturetarget_prop.set_unit("deg C");
	//	standard_unit	not set for temperatureTarget
	//	display_unit	not set for temperatureTarget
	temperaturetarget_prop.set_format("%6.2f");
	//	max_value	not set for temperatureTarget
	//	min_value	not set for temperatureTarget
	//	max_alarm	not set for temperatureTarget
	//	min_alarm	not set for temperatureTarget
	//	max_warning	not set for temperatureTarget
	//	min_warning	not set for temperatureTarget
	//	delta_t	not set for temperatureTarget
	//	delta_val	not set for temperatureTarget
	
	temperaturetarget->set_default_properties(temperaturetarget_prop);
	//	Not Polled
	temperaturetarget->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(temperaturetarget);

	//	Attribute : gain
	gainAttrib	*gain = new gainAttrib();
	Tango::UserDefaultAttrProp	gain_prop;
	gain_prop.set_description("Define the gain of the detector [LOW, MEDIUM, HIGH]");
	//	label	not set for gain
	//	unit	not set for gain
	//	standard_unit	not set for gain
	//	display_unit	not set for gain
	//	format	not set for gain
	//	max_value	not set for gain
	//	min_value	not set for gain
	//	max_alarm	not set for gain
	//	min_alarm	not set for gain
	//	max_warning	not set for gain
	//	min_warning	not set for gain
	//	delta_t	not set for gain
	//	delta_val	not set for gain
	
	gain->set_default_properties(gain_prop);
	//	Not Polled
	gain->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(gain);

	//	Attribute : adcRate
	adcRateAttrib	*adcrate = new adcRateAttrib();
	Tango::UserDefaultAttrProp	adcrate_prop;
	adcrate_prop.set_description("Define the speed at which pixels are digitized (MHz)");
	//	label	not set for adcRate
	//	unit	not set for adcRate
	//	standard_unit	not set for adcRate
	adcrate_prop.set_display_unit("MHz");
	//	format	not set for adcRate
	//	max_value	not set for adcRate
	//	min_value	not set for adcRate
	//	max_alarm	not set for adcRate
	//	min_alarm	not set for adcRate
	//	max_warning	not set for adcRate
	//	min_warning	not set for adcRate
	//	delta_t	not set for adcRate
	//	delta_val	not set for adcRate
	
	adcrate->set_default_properties(adcrate_prop);
	//	Not Polled
	adcrate->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(adcrate);


	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(TeledynePIClass::attribute_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::pipe_factory()
 *	Description : Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void TeledynePIClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(TeledynePIClass::pipe_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::pipe_factory_before
	/*----- PROTECTED REGION ID(TeledynePIClass::pipe_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::command_factory()
 *	Description : Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void TeledynePIClass::command_factory()
{
	/*----- PROTECTED REGION ID(TeledynePIClass::command_factory_before) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::command_factory_before


	/*----- PROTECTED REGION ID(TeledynePIClass::command_factory_after) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the ceated attribute list
 */
//--------------------------------------------------------
void TeledynePIClass::create_static_attribute_list(vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	cout2 << defaultAttList.size() << " attributes in default list" << endl;

	/*----- PROTECTED REGION ID(TeledynePIClass::create_static_att_list) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		TeledynePIClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void TeledynePIClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((string)(*devlist_ptr)[i]).c_str());
		TeledynePI *dev = static_cast<TeledynePI *> (dev_impl);

		vector<Tango::Attribute *> &dev_att_list = dev->get_device_attr()->get_attribute_list();
		vector<Tango::Attribute *>::iterator ite_att;
		for (ite_att=dev_att_list.begin() ; ite_att != dev_att_list.end() ; ++ite_att)
		{
			string att_name((*ite_att)->get_name_lower());
			if ((att_name == "state") || (att_name == "status"))
				continue;
			vector<string>::iterator ite_str = find(defaultAttList.begin(), defaultAttList.end(), att_name);
			if (ite_str == defaultAttList.end())
			{
				cout2 << att_name << " is a UNWANTED dynamic attribute for device " << (*devlist_ptr)[i] << endl;
				Tango::Attribute &att = dev->get_device_attr()->get_attr_by_name(att_name.c_str());
				dev->remove_attribute(att_list[att.get_attr_idx()], true, false);
				--ite_att;
			}
		}
	}
	/*----- PROTECTED REGION ID(TeledynePIClass::erase_dynamic_attributes) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : TeledynePIClass::get_attr_object_by_name()
 *	Description : returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *TeledynePIClass::get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname)
{
	vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(TeledynePIClass::Additional Methods) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	TeledynePIClass::Additional Methods
} //	namespace
