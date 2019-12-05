//+=============================================================================
//
// file :         Factory.cpp
//
// description : This module handles the creation of the main lima object (CtControl) for each type of camera
//
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
#include <Factory.h>

#include <iostream>

bool ControlFactory::m_is_created = false;



//-----------------------------------------------------------------------------------------
void ControlFactory::initialize()
{
	YAT_LOG_INFO("initialize the factory control" );	
    m_control = 0;
    m_camera	 = 0;
    m_interface = 0;

    m_device_name_generic = "none";
    m_device_name_specific = "none";

#ifdef LAYOUT_ENABLED    
    m_device_name_layout = "none";
#endif

#ifdef ROICOUNTERS_ENABLED     
    m_device_name_roicounters = "none";
#endif  

#ifdef MASK_ENABLED    
    m_device_name_mask = "none";
#endif
    m_status.str("");
    m_state = Tango::INIT;
}

//-----------------------------------------------------------------------------------------
yat::Mutex& ControlFactory::get_global_mutex()
{
    return m_lock;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::create_control(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(m_lock);
	YAT_LOG_INFO("create the factory control" );	
    try
    {
        //get the tango device/instance
        if (!ControlFactory::m_is_created)
        {
            initialize();
			
			//- Set Serialisation mode
			//- this is the default mode
			YAT_LOG_INFO("Set Serialisation Model : BY_DEVICE");
			Tango::Util::instance()->set_serial_model(Tango::SerialModel::BY_DEVICE);			

            {
                std::string specific = detector_type;
                Tango::DbDatum db_datum;
                m_device_name_generic = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, specific);
                db_datum >> m_device_name_specific;
            }

#ifdef LAYOUT_ENABLED
            {
                std::string layout = "Layout";
                Tango::DbDatum db_datum;
                m_device_name_generic = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, layout);
                db_datum >> m_device_name_layout;
            }
#endif         

#ifdef ROICOUNTERS_ENABLED
            {
                std::string roicounters = "RoiCounters";
                Tango::DbDatum db_datum;
                m_device_name_generic = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, roicounters);
                db_datum >> m_device_name_roicounters;
            }
#endif     
			
#ifdef MASK_ENABLED
            {
                std::string mask = "Mask";
                Tango::DbDatum db_datum;
                m_device_name_generic = Tango::Util::instance()->get_ds_name();
                db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, mask);
                db_datum >> m_device_name_mask;
            }
#endif         
			
        }

#ifdef SIMULATOR_ENABLED
        if (detector_type == "SimulatorCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = static_cast<void*> (new Simulator::Camera());
                m_interface = static_cast<void*> (new Simulator::Interface(*static_cast<Simulator::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Simulator::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef AVIEX_ENABLED
        if (detector_type == "AviexCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorID"));
                db_data.push_back(Tango::DbDatum("MxDatabaseFileFullName"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string detector_id;
                std::string database_file;
                db_data[0] >> detector_id;
                db_data[1] >> database_file;
                m_camera = static_cast<void*> (new Aviex::Camera(detector_id, database_file));

                m_interface = static_cast<void*> (new Aviex::Interface(*static_cast<Aviex::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Aviex::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef BASLER_ENABLED
        if (detector_type == "BaslerCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorTimeout"));
                db_data.push_back(Tango::DbDatum("DetectorPacketSize"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;
                long detector_timeout = 11000;
                db_data[1] >> detector_timeout;
                long packet_size = -1;
                db_data[2] >> packet_size;
                m_camera = static_cast<void*> (new Basler::Camera(camera_ip, packet_size));
                static_cast<Basler::Camera*> (m_camera)->setTimeout(detector_timeout);

                m_interface = static_cast<void*> (new Basler::Interface(*static_cast<Basler::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Basler::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef IMXPAD_ENABLED
        if (detector_type == "ImXpad")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("HostName"));
                db_data.push_back(Tango::DbDatum("Port"));
				db_data.push_back(Tango::DbDatum("ModuleMask"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string host_name;
                long port;
				std::string module_mask_str;
                db_data[0] >> host_name;
                db_data[1] >> port;
				db_data[2] >> module_mask_str;
				
				unsigned int module_mask_hexa;
				std::stringstream ss;
				ss << std::hex << module_mask_str;
				ss >> module_mask_hexa;	
				
				std::cout<<"module_mask_str = "<<module_mask_str<<std::endl;
				std::cout<<"module_mask_hexa = "<<module_mask_hexa<<std::endl;
                m_camera = static_cast<void*> (new imXpad::Camera(host_name, port, module_mask_hexa));

                m_interface = static_cast<void*> (new imXpad::Interface(*static_cast<imXpad::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<imXpad::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif
        
#ifdef XPAD_ENABLED
        if (detector_type == "XpadPixelDetector")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("XpadModel"));
                db_data.push_back(Tango::DbDatum("CalibrationAdjustingNumber"));
                db_data.push_back(Tango::DbDatum("MinLatencyTimeMs"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string xpad_model;
                Tango::DevULong calibration_adjusting_number;
                Tango::DevDouble min_latency_time_ms;

                db_data[0] >> xpad_model;
                db_data[1] >> calibration_adjusting_number;
                db_data[2] >> min_latency_time_ms;

                m_camera = static_cast<void*> (new Xpad::Camera(xpad_model));
                static_cast<Xpad::Camera*> (m_camera)->setCalibrationAdjustingNumber(calibration_adjusting_number);
                static_cast<Xpad::Camera*> (m_camera)->setMinLatencyTimeMs(min_latency_time_ms);

                m_interface = static_cast<void*> (new Xpad::Interface(*static_cast<Xpad::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Xpad::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PILATUS_ENABLED
        if (detector_type == "PilatusPixelDetector")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorCameraDefFileName"));
                db_data.push_back(Tango::DbDatum("UseReader"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip = "127.0.0.1";
                std::string camera_def = "camera.def";
                long camera_port = 6666;
                bool use_reader = false;
                unsigned long reader_timeout = 10000;  //in ms

                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> camera_def;
                db_data[3] >> use_reader;
                db_data[4] >> reader_timeout;

                m_camera = static_cast<void*> (new Pilatus::Camera(camera_ip.c_str(), camera_port, const_cast<std::string&> (camera_def)));
                if(m_camera)
                {
                    if(use_reader)
                        static_cast<Pilatus::Camera*> (m_camera)->enableReaderWatcher();
                    else
                        static_cast<Pilatus::Camera*> (m_camera)->disableReaderWatcher();
                }

                m_interface = static_cast<void*> (new Pilatus::Interface(*static_cast<Pilatus::Camera*> (m_camera)));
                if(m_interface)
                    static_cast<Pilatus::Interface*> (m_interface)->setTimeout(reader_timeout / 1000.);
                m_control = new CtControl(static_cast<Pilatus::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef MARCCD_ENABLED
        if (detector_type == "MarCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                db_data.push_back(Tango::DbDatum("DetectorPort"));
                db_data.push_back(Tango::DbDatum("DetectorTargetPath"));
                db_data.push_back(Tango::DbDatum("ReaderTimeout"));
				db_data.push_back(Tango::DbDatum("ReaderNbRetry"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                std::string img_path;
                unsigned long camera_port = 2222;
                unsigned short reader_timeout = 10000;
				long reader_nb_retry = 3;

                db_data[0] >> camera_ip;
                db_data[1] >> camera_port;
                db_data[2] >> img_path;
                db_data[3] >> reader_timeout;
				db_data[4] >> reader_nb_retry;

                m_camera = static_cast<void*> (new Marccd::Camera(camera_ip.c_str(), camera_port, img_path));
                m_interface = static_cast<void*> (new Marccd::Interface(*static_cast<Marccd::Camera*> (m_camera)));
                if (m_interface)
				{
                    static_cast<Marccd::Interface*> (m_interface)->setTimeout(reader_timeout / 1000);
					static_cast<Marccd::Interface*> (m_interface)->setNbRetry(reader_nb_retry);
				}

                m_control = new CtControl(static_cast<Marccd::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef MAXIPIX_ENABLED
        if (detector_type == "Maxipix")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("EspiaDeviceNumber"));
                db_data.push_back(Tango::DbDatum("ConfigurationPath"));
                db_data.push_back(Tango::DbDatum("ConfigurationName"));
                db_data.push_back(Tango::DbDatum("UseReconstruction"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long espia_device_number = -1;
                std::string config_path;
                std::string config_name;
                bool use_reconstruction = false;

                db_data[0] >> espia_device_number;
                db_data[1] >> config_path;
                db_data[2] >> config_name;
                db_data[3] >> use_reconstruction;

                m_camera = static_cast<void*> (new Maxipix::Camera(espia_device_number, config_path, config_name, use_reconstruction));
                m_interface = static_cast<void*> (new Maxipix::Interface(*static_cast<Maxipix::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Maxipix::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PROSILICA_ENABLED
        if (detector_type == "ProsilicaCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip;
                db_data[0] >> camera_ip;

                m_camera = static_cast<void*> (new Prosilica::Camera(camera_ip.c_str()));
                m_interface = static_cast<void*> (new Prosilica::Interface(static_cast<Prosilica::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Prosilica::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR_ENABLED
        if (detector_type == "AndorCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new Andor::Camera("Not Used At Soleil", camera_num));
                m_interface = static_cast<void*> (new Andor::Interface(*static_cast<Andor::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Andor::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PRINCETON_ENABLED
        if (detector_type == "PrincetonCCD")
        {

            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new RoperScientific::Camera(camera_num));
                m_interface = static_cast<void*> (new RoperScientific::Interface(*static_cast<RoperScientific::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<RoperScientific::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PCO_ENABLED
        if (detector_type == "Pco")
        {
            if (!ControlFactory::m_is_created)
            {
				//- Set Serialisation mode
				//- this allow dynamic attr in pco specific device
				YAT_LOG_INFO("Set Serialisation Model : BY_PROCESS");
				Tango::Util::instance()->set_serial_model(Tango::SerialModel::BY_PROCESS);
	
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("SerialNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                string params,serial_number;
                db_data[0] >> serial_number;
                params = "sn = " + serial_number;

                m_camera = static_cast<void*> (new Pco::Camera(params.c_str()));
                m_interface = static_cast<void*> (new Pco::Interface(static_cast<Pco::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Pco::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef PERKINELMER_ENABLED
        if (detector_type == "PerkinElmer")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = 0;
                m_interface = static_cast<void*> (new PerkinElmer::Interface());
                m_control = new CtControl(static_cast<PerkinElmer::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif


#ifdef MERLIN_ENABLED
        if (detector_type == "Merlin")
        {
            if(!ControlFactory::m_is_created)
            {
                m_camera = 0;
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("HostName"));
                db_data.push_back(Tango::DbDatum("CmdPort"));
                db_data.push_back(Tango::DbDatum("DataPort"));
                db_data.push_back(Tango::DbDatum("ImageWidth"));
                db_data.push_back(Tango::DbDatum("ImageHeight"));
                db_data.push_back(Tango::DbDatum("Chips"));
                db_data.push_back(Tango::DbDatum("Simulate"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string hostName;
                long cmdPort;
                long dataPort;
                long chips;
                long imageWidth;
                long imageHeight;
                bool simulate;
                db_data[0] >> hostName;
                db_data[1] >> cmdPort;
                db_data[2] >> dataPort;
                db_data[3] >> imageWidth;
                db_data[4] >> imageHeight;
                db_data[5] >> chips;
                db_data[6] >> simulate;

                m_camera = static_cast<void*> (new Merlin::Camera(hostName, cmdPort, dataPort, imageWidth, imageHeight, chips, simulate));
                m_interface = static_cast<void*> (new Merlin::Interface(*static_cast<Merlin::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Merlin::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef ANDOR3_ENABLED
        if (detector_type == "Andor3")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("BitFlowPath"));
                db_data.push_back(Tango::DbDatum("CameraNumber"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string bit_flow_path;
                long camera_number;
                db_data[0] >> bit_flow_path;
                db_data[1] >> camera_number;

                m_camera = static_cast<void*> (new Andor3::Camera(bit_flow_path, camera_number));
                m_interface = static_cast<void*> (new Andor3::Interface(*static_cast<Andor3::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Andor3::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef VIEWORKSVP_ENABLED
        if (detector_type == "VieworksVP")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("SisoPath"));
                db_data.push_back(Tango::DbDatum("BoardIndex"));
                db_data.push_back(Tango::DbDatum("CameraPort"));
                db_data.push_back(Tango::DbDatum("AppletName"));
                db_data.push_back(Tango::DbDatum("DMAIndex"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string siso_path;
                long board_index;
                long camera_port;
                std::string applet_name;
                unsigned long dma_index;
                db_data[0] >> siso_path;
                db_data[1] >> board_index;
                db_data[2] >> camera_port;
                db_data[3] >> applet_name;
                db_data[4] >> dma_index;

                m_camera = static_cast<void*> (new VieworksVP::Camera(siso_path, board_index, camera_port, applet_name, dma_index));
                m_interface = static_cast<void*> (new VieworksVP::Interface(*static_cast<VieworksVP::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<VieworksVP::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef HAMAMATSU_ENABLED
        if (detector_type == "Hamamatsu")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorNum"));
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                long camera_num;
                db_data[0] >> camera_num;

                m_camera = static_cast<void*> (new Hamamatsu::Camera("Not config path", camera_num));
                m_interface = static_cast<void*> (new Hamamatsu::Interface(*(static_cast<Hamamatsu::Camera*> (m_camera))));
                m_control = new CtControl(static_cast<Hamamatsu::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef EIGER_ENABLED
        if (detector_type == "Eiger")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("DetectorIP"));
				db_data.push_back(Tango::DbDatum("TimestampType"));
				db_data.push_back(Tango::DbDatum("DownloadDataFile"));
				
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string camera_ip = "127.0.0.1";
				std::string timestamp_type = "RELATIVE";
				bool must_download = false;
                db_data[0] >> camera_ip;
				db_data[1] >> timestamp_type;
				db_data[2] >> must_download;
				transform(timestamp_type.begin(), timestamp_type.end(), timestamp_type.begin(), ::toupper);
                m_camera = static_cast<void*> (new Eiger::Camera(camera_ip));
				static_cast<Eiger::Camera*> (m_camera)->setTimestampType(timestamp_type);
                m_interface = static_cast<void*> (new Eiger::Interface(*(static_cast<Eiger::Camera*> (m_camera))));
                if (m_interface)
				{
                    static_cast<Eiger::Interface*> (m_interface)->setDownloadDataFile(must_download);				
				}				
                m_control = new CtControl(static_cast<Eiger::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif           

#ifdef UVIEW_ENABLED
        if (detector_type == "UviewCCD")
        {
            if (!ControlFactory::m_is_created)
            {
                m_camera = static_cast<void*> (new Uview::Camera());
                m_interface = static_cast<void*> (new Uview::Interface(*static_cast<Uview::Camera*> (m_camera)));
                m_control = new CtControl(static_cast<Uview::Interface*> (m_interface));

                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef SLSJUNGFRAU_ENABLED
        if (detector_type == "SlsJungfrau")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data            ;
                std::string   config_file_name   ;
                double        readout_time       ;
                long          receiver_fifo_depth;
                long          frame_packet_number;
                
                // configuration complete path
                db_data.push_back(Tango::DbDatum("ConfigFileName"));
                
                // readout time of the camera
                db_data.push_back(Tango::DbDatum("ExpertReadoutTime"));
                
                // Number of frames in the receiver memory
                db_data.push_back(Tango::DbDatum("ExpertReceiverFifoDepth"));

                // Number of packets we should get in each receiver frame
                db_data.push_back(Tango::DbDatum("ExpertFramePacketNumber"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                db_data[0] >> config_file_name   ;
                db_data[1] >> readout_time       ;
                db_data[2] >> receiver_fifo_depth;
                db_data[3] >> frame_packet_number;

                // create and initialize the camera and create interface and control  
                m_camera    = static_cast<void*> (new SlsJungfrau::Camera(config_file_name, readout_time, receiver_fifo_depth, frame_packet_number));
                m_interface = static_cast<void*> (new SlsJungfrau::Interface(*(static_cast<SlsJungfrau::Camera*> (m_camera))));
                m_control   = new CtControl(static_cast<SlsJungfrau::Interface*> (m_interface));
               
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif           


#ifdef LAMBDA_ENABLED
        if (detector_type == "Lambda")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                std::string config_file_path = "/opt/xsp/config";
                bool distortion_correction = true;

                // configuration path
                db_data.push_back(Tango::DbDatum("ConfigFilesPath"));

                // distortion correction
                db_data.push_back(Tango::DbDatum("DistortionCorrection"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                db_data[0] >> config_file_path;
                db_data[1] >> distortion_correction;

                m_camera    = static_cast<void*> (new Lambda::Camera(config_file_path, distortion_correction));
                m_interface = static_cast<void*> (new Lambda::Interface(*static_cast<Lambda::Camera*> (m_camera)));
                m_control   = new CtControl(static_cast<Lambda::Interface*> (m_interface));

                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef DHYANA_ENABLED
        if (detector_type == "Dhyana")
        {
            if (!ControlFactory::m_is_created)
            {
				unsigned short time_period = 1;
                Tango::DbData db_data;
				db_data.push_back(Tango::DbDatum("__ExpertTimerPeriod"));							
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                db_data[0] >> time_period   ;				
                m_camera = static_cast<void*> (new Dhyana::Camera(time_period));
                m_interface = static_cast<void*> (new Dhyana::Interface(*(static_cast<Dhyana::Camera*> (m_camera))));
                m_control = new CtControl(static_cast<Dhyana::Interface*> (m_interface));

                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif

#ifdef UFXC_ENABLED
        if (detector_type == "Ufxc")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                db_data.push_back(Tango::DbDatum("ConfigIpAddress"));
				db_data.push_back(Tango::DbDatum("ConfigPort"));
				db_data.push_back(Tango::DbDatum("SFP1IpAddress"));
				db_data.push_back(Tango::DbDatum("SFP1Port"));
				db_data.push_back(Tango::DbDatum("SFP2IpAddress"));
				db_data.push_back(Tango::DbDatum("SFP2Port"));
				db_data.push_back(Tango::DbDatum("SFP3IpAddress"));
				db_data.push_back(Tango::DbDatum("SFP3Port"));
				db_data.push_back(Tango::DbDatum("Timeout"));
				db_data.push_back(Tango::DbDatum("GeometricalCorrectionEnabled"));
				db_data.push_back(Tango::DbDatum("StackFramesSumEnabled"));
				
                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);
                std::string config_ip_address = "127.0.0.1";
				unsigned long config_port = 0;
				std::string SFP1_ip_address = "127.0.0.1";
				unsigned long SFP1_port = 0;				
				std::string SFP2_ip_address = "127.0.0.1";
				unsigned long SFP2_port = 0;	
				std::string SFP3_ip_address = "127.0.0.1";
				unsigned long SFP3_port = 0;	
				unsigned long timeout = 0;
				bool geometrical_correction_enabled = true ;
				bool stack_frames_sum_enabled = true ;
				
                db_data[0] >> config_ip_address;
				db_data[1] >> config_port;
                db_data[2] >> SFP1_ip_address;
				db_data[3] >> SFP1_port;
                db_data[4] >> SFP2_ip_address;
				db_data[5] >> SFP2_port;
                db_data[6] >> SFP3_ip_address;
				db_data[7] >> SFP3_port;
				db_data[8] >> timeout;
				db_data[9] >> geometrical_correction_enabled;
				db_data[10]>> stack_frames_sum_enabled;
				
                m_camera = static_cast<void*> (new Ufxc::Camera(config_ip_address, config_port,
																SFP1_ip_address, SFP1_port,
																SFP2_ip_address, SFP2_port,
																SFP3_ip_address, SFP3_port,
																timeout,
																geometrical_correction_enabled,
																stack_frames_sum_enabled
																));
                m_interface = static_cast<void*> (new Ufxc::Interface(*(static_cast<Ufxc::Camera*> (m_camera))));
                m_control = new CtControl(static_cast<Ufxc::Interface*> (m_interface));

                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif
				
#ifdef XSPRESS3_ENABLED
        if (detector_type == "Xspress3")
        {
            if (!ControlFactory::m_is_created)
            {
                Tango::DbData db_data;
                std::string   base_ip_adress = "192.168.0.1";
                std::string   base_mac_address = "02.00.00.00.00.00";				
                long		  base_port = 30123;				 
                long		  card_index = 0;
                std::string   directory_name = "/etc/xspress3/calibration/me4_mar_2018/settings/";
                long          max_frames = 16384;
                long          nb_cards = 2;
                long          nb_chans = 4;
		bool          no_udp = false;
                
                // configuration complete path
                db_data.push_back(Tango::DbDatum("BaseIPAdress"));
                db_data.push_back(Tango::DbDatum("BaseMacAddress"));
                db_data.push_back(Tango::DbDatum("BasePort"));
                db_data.push_back(Tango::DbDatum("CardIndex"));
                db_data.push_back(Tango::DbDatum("DirectoryName"));
                db_data.push_back(Tango::DbDatum("MaxFrames"));				
                db_data.push_back(Tango::DbDatum("NbCards"));				
                db_data.push_back(Tango::DbDatum("NbChans"));				
		db_data.push_back(Tango::DbDatum("NoUDP"));

                (Tango::Util::instance()->get_database())->get_device_property(m_device_name_specific, db_data);

                db_data[0] >> base_ip_adress;
                db_data[1] >> base_mac_address;
                db_data[2] >> base_port;
                db_data[3] >> card_index;
                db_data[4] >> directory_name;
                db_data[5] >> max_frames;
                db_data[6] >> nb_cards;
                db_data[7] >> nb_chans;
		db_data[8] >> no_udp;
				
				std::cout<<"- base_ip_adress = "<<base_ip_adress<<std::endl;
				std::cout<<"- base_mac_address = "<<base_mac_address<<std::endl;
				std::cout<<"- base_port = "<<base_port<<std::endl;
				std::cout<<"- card_index = "<<card_index<<std::endl;
				std::cout<<"- directory_name = "<<directory_name<<std::endl;
				std::cout<<"- max_frames = "<<max_frames<<std::endl;
				std::cout<<"- nb_cards = "<<nb_cards<<std::endl;
				std::cout<<"- nb_chans = "<<nb_chans<<std::endl;
				std::cout<<"- no_udp = "<<no_udp<<std::endl;
				
                // create and initialize the camera and create interface and control  
                m_camera    = static_cast<void*> (new Xspress3::Camera(nb_cards,
																	   max_frames,
																	   base_ip_adress,
																	   base_port,
																	   base_mac_address,
																	   nb_chans,
																	   false,//create scope module
																	   "NULL",//scope module name
																	   0,//debug
																	   card_index,
																	   no_udp,
																	   directory_name));

		static_cast<Xspress3::Camera*> (m_camera)->setUseDtc(false);
                m_interface = static_cast<void*> (new Xspress3::Interface(*(static_cast<Xspress3::Camera*> (m_camera))));
                m_control   = new CtControl(static_cast<Xspress3::Interface*> (m_interface));
                ControlFactory::m_is_created = true;
                return m_control;
            }
        }
#endif
		
        if (!ControlFactory::m_is_created)
        {
            string strMsg = "Unable to create the lima control object : Unknown Detector Type : ";
            strMsg += detector_type;
            throw LIMA_HW_EXC(Error, strMsg);
        }

    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch (Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch (...)
    {
        throw LIMA_HW_EXC(Error, "Unable to create the lima control object : Unknown Exception");
    }

    return m_control;
}

//-----------------------------------------------------------------------------------------
CtControl* ControlFactory::get_control(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(m_lock);
    if (!ControlFactory::m_is_created)
    {
        std::stringstream ssMsg("");
        ssMsg << "Unable to get the lima control of " << "(" << detector_type << ") !" << endl;
        throw LIMA_HW_EXC(Error, ssMsg.str());
    }
    return m_control;
}

//-----------------------------------------------------------------------------------------
void ControlFactory::reset(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(m_lock);
	YAT_LOG_INFO("reset the factory control" );	
    try
    {
        if (ControlFactory::m_is_created)
        {
            ControlFactory::m_is_created = false;
            if (m_control)
            {
                delete m_control;
                m_control = 0;
            }

            if (m_camera)
            {
#ifdef SIMULATOR_ENABLED        
                if (detector_type == "SimulatorCCD")
                {
                    delete (static_cast<Simulator::Camera*> (m_camera));
                }
#endif

#ifdef AVIEX_ENABLED        
                if (detector_type == "AviexCCD")
                {
                    delete (static_cast<Aviex::Camera*> (m_camera));
                }
#endif

#ifdef BASLER_ENABLED        
                if (detector_type == "BaslerCCD")
                {
                    delete (static_cast<Basler::Camera*> (m_camera));
                }
#endif

#ifdef IMXPAD_ENABLED        
                if (detector_type == "ImXpad")
                {
                    delete (static_cast<imXpad::Camera*> (m_camera));
                }
#endif                

#ifdef XPAD_ENABLED        
                if (detector_type == "XpadPixelDetector")
                {
                    delete (static_cast<Xpad::Camera*> (m_camera));
                }
#endif

#ifdef PILATUS_ENABLED        
                if (detector_type == "PilatusPixelDetector")
                {
                    delete (static_cast<Pilatus::Camera*> (m_camera));
                }
#endif

#ifdef MARCCD_ENABLED        
                if (detector_type == "MarCCD")
                {
                    delete (static_cast<Marccd::Camera*> (m_camera));
                }
#endif  

#ifdef MAXIPIX_ENABLED        
                if (detector_type == "Maxipix")
                {
                    delete (static_cast<Maxipix::Camera*> (m_camera));
                }
#endif 

#ifdef PROSILICA_ENABLED        
                if (detector_type == "ProsilicaCCD")
                {
                    delete (static_cast<Prosilica::Camera*> (m_camera));
                }
#endif 

#ifdef ANDOR_ENABLED        
                if (detector_type == "AndorCCD")
                {
                    delete (static_cast<Andor::Camera*> (m_camera));
                }
#endif     

#ifdef PRINCETON_ENABLED        
                if (detector_type == "PrincetonCCD")
                {
                    delete (static_cast<RoperScientific::Camera*> (m_camera));
                }
#endif         

#ifdef PCO_ENABLED        
                if (detector_type == "Pco")
                {
                    delete (static_cast<Pco::Camera*> (m_camera));
                }
#endif 

#ifdef PERKINELMER_ENABLED        
                if (detector_type == "PerkinElmer")
                {
                    //NOP
                }
#endif 

#ifdef MERLIN_ENABLED        
                if (detector_type == "Merlin")
                {
                    delete (static_cast<Merlin::Camera*> (m_camera));
                }
#endif   

#ifdef ANDOR3_ENABLED        
                if (detector_type == "Andor3")
                {
                    delete (static_cast<Andor3::Camera*> (m_camera));
                }
#endif        

#ifdef VIEWORKSVP_ENABLED        
                if (detector_type == "VieworksVP")
                {
                    delete (static_cast<VieworksVP::Camera*> (m_camera));
                }
#endif              

#ifdef HAMAMATSU_ENABLED        
                if (detector_type == "Hamamatsu")
                {
                    delete (static_cast<Hamamatsu::Camera*> (m_camera));
                }
#endif    

#ifdef EIGER_ENABLED
                if (detector_type == "Eiger")
                {
                    delete (static_cast<Eiger::Camera*> (m_camera));
                }
#endif

#ifdef UVIEW_ENABLED        
                if (detector_type == "UviewCCD")
                {
                    delete (static_cast<Uview::Camera*> (m_camera));
                }
#endif     

#ifdef SLSJUNGFRAU_ENABLED        
                if (detector_type == "SlsJungfrau")
                {
                    delete (static_cast<SlsJungfrau::Camera*> (m_camera));
                }
#endif     


#ifdef LAMBDA_ENABLED        
                if (detector_type == "Lambda")
                {
                    delete (static_cast<Lambda::Camera*> (m_camera));
                }
#endif
				
#ifdef DHYANA_ENABLED        
                if (detector_type == "Dhyana")
                {
					delete (static_cast<Dhyana::Camera*> (m_camera));				
                }
#endif

#ifdef UFXC_ENABLED        
                if (detector_type == "Ufxc")
                {
					delete (static_cast<Ufxc::Camera*> (m_camera));				
                }
#endif
				
#ifdef XSPRESS3_ENABLED        
                if (detector_type == "Xspress3")
                {
                    delete (static_cast<Xspress3::Camera*> (m_camera));
                }
#endif  

				
                m_camera = 0;
            }

			
            if (m_interface)
            {
                delete m_interface;
                m_interface = 0;
            }
        }
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
    catch (Exception& e)
    {
        throw LIMA_HW_EXC(Error, e.getErrMsg());
    }
    catch (...)
    {
        throw LIMA_HW_EXC(Error, "reset : Unknown Exception");
    }
}

//-----------------------------------------------------------------------------------------
//- force Init() on the specific device.
//-----------------------------------------------------------------------------------------
void ControlFactory::init_specific_device(const std::string& detector_type)
{
    yat::AutoMutex<> _lock(m_lock);
	YAT_LOG_INFO("init the specific device via factory" );		
    try
    {
        //get the tango device/instance
        if (!ControlFactory::m_is_created)
        {
            std::string detector = detector_type;
            Tango::DbDatum db_datum;
            m_device_name_generic = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, detector);
            db_datum >> m_device_name_specific;
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_specific))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_specific))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }

#ifdef LAYOUT_ENABLED        
    try
    {
        //@@@TODO and if not exist ?? get the tango device/instance for layout
        if (!ControlFactory::m_is_created)
        {
            std::string layout = "Layout";
            Tango::DbDatum db_datum;
            m_device_name_generic = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, layout);
            db_datum >> m_device_name_layout;
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_layout))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_layout))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        ////throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
#endif

#ifdef ROICOUNTERS_ENABLED        
    try
    {
        //@@@TODO and if not exist ?? get the tango device/instance for roicounters
        if (!ControlFactory::m_is_created)
        {
            std::string roicounters = "RoiCounters";
            Tango::DbDatum db_datum;
            m_device_name_generic = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, roicounters);
            db_datum >> m_device_name_roicounters;
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_roicounters))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_roicounters))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        ////throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
#endif 
	
#ifdef MASK_ENABLED        
    try
    {
        //@@@TODO and if not exist ?? get the tango device/instance for layout
        if (!ControlFactory::m_is_created)
        {
            std::string mask = "Mask";
            Tango::DbDatum db_datum;
            m_device_name_generic = Tango::Util::instance()->get_ds_name();
            db_datum = (Tango::Util::instance()->get_database())->get_device_name(m_device_name_generic, mask);
            db_datum >> m_device_name_mask;
        }
        (Tango::Util::instance()->get_device_by_name(m_device_name_mask))->delete_device();
        (Tango::Util::instance()->get_device_by_name(m_device_name_mask))->init_device();
    }
    catch (Tango::DevFailed& df)
    {
        //- rethrow exception
        ////throw LIMA_HW_EXC(Error, std::string(df.errors[0].desc).c_str());
    }
#endif
	
}

//-----------------------------------------------------------------------------------------
//- call dev_state() command of the generic device.
//-----------------------------------------------------------------------------------------
Tango::DevState ControlFactory::get_state(void)
{    
    yat::AutoMutex<> _lock(m_lock);
    CtControl::Status ctStatus;
    m_control->getStatus(ctStatus);

    switch(ctStatus.AcquisitionStatus)
    {
        case lima::AcqReady:
        {
            set_state(Tango::STANDBY);
            set_status("Waiting for a user request ...\n");
        }
            break;

        case lima::AcqRunning:
        {
            set_state(Tango::RUNNING);
            set_status("Acquisition in Progress ...\n");
        }
            break;

        case lima::AcqConfig:
        {
            set_state(Tango::DISABLE);
            set_status("Configuration/Calibration in Progress ...\n");
        }
            break;

        default:
        {
            set_state(Tango::FAULT);
            set_status("Error has occured !\n");
        }
            break;
    }
    return m_state;
}
//-----------------------------------------------------------------------------------------
//- call dev_status() command of the generic device.
//-----------------------------------------------------------------------------------------
std::string ControlFactory::get_status(void)
{
    yat::AutoMutex<> _lock(m_lock);
    return (m_status.str() + m_event_status.str());
}

//-----------------------------------------------------------------------------------------
void ControlFactory::set_state(Tango::DevState state)
{
    yat::AutoMutex<> _lock(m_lock);
    m_state = state;
}

//-----------------------------------------------------------------------------------------
void ControlFactory::set_status(const std::string& status)
{
    yat::AutoMutex<> _lock(m_lock);
    m_status.str("");
    m_status << status.c_str() << endl;

}
//-----------------------------------------------------------------------------------------
void ControlFactory::set_event_status(const std::string& status)
{
    yat::AutoMutex<> _lock(m_lock);
    m_event_status.str("");
	m_event_status <<"------------------------"<< endl;	
    m_event_status << status << endl;
}
//-----------------------------------------------------------------------------------------


