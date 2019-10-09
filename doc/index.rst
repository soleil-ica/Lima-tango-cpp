Lima C++ TANGO device server
=================================

This is the C++ **LimaDetector** Tango device server developped at SOLEIL.

.. image:: Soleil_Lima_Device.png
   :scale: 60 %
   :alt: LimaDetector device server structure
   :align: right

This device server provides several Tango classes:

- **LimaDetector** : Generic class for the standard camera control
- **CameraType** : A camera specific class for the camera configuration (see the list below)
- Optionnal classes:

  - **RoiCounters** : Allows to set Rois and get some statistic for each roi (sum, average, std ...)
  - **Layout** : Allows to modify the original image (flip, rotation, additions ...)
  - **Mask** : Allows to define a mask on the original image (force some pixels to 0) 
  - **FlatField** : Allows to modify the original image by substracting a flatfield image (not yet available)
  - **BackgroundSubstraction** : Allows to modify the original image by substracting a background image (not yet available)

--------------------------

.. toctree::
   :maxdepth: 1

   LimaDetector <LimaDetector/limadetector>
  
--------------------------

.. toctree::
   :maxdepth: 1

   AndorCCD <AndorCCD/andorccd>
   AviexCCD <AviexCCD/aviexccd>
   BaslerCCD <BaslerCCD/baslerccd>
   Eiger <Eiger/eiger>
   Hamamatsu <Hamamatsu/hamamatsu>
   ImXpad <ImXpad/imxpad>
   Lambda <Lambda/lambda>
   MarCCD <MarCCD/marccd>
   Maxipix <Maxipix/maxipix>
   Merlin <Merlin/merlin>
   Pco <Pco/pco>
   PerkinElmer <PerkinElmer/perkinelmer>
   PilatusPixelDetector <PilatusPixelDetector/pilatuspixeldetector>
   PrincetonCCD <PrincetonCCD/princetonccd>
   ProsilicaCCD <ProsilicaCCD/prosilicaccd>
   SimulatorCCD <SimulatorCCD/simulatorccd>
   SlsJungfrau <SlsJungfrau/slsjungfrau>
   Ufxc <Ufxc/ufxc>
   Uview <Uview/uview>
   XpadPixelDetector <XpadPixelDetector/xpadpixeldetector>
  
--------------------------

.. toctree::
   :maxdepth: 1

   RoiCounters <RoiCounters/roicounters>
   Layout <Layout/layout>
   Mask <Mask/mask>
