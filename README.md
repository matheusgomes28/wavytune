# WavyTune

Description and name will probably be changed in the future.

WavyTune will be an audio visualizer which can be compiled for for the RaspberryPi. At the current stage, the drawing engine and the audio engine are still being developed. The tasks involved in this project are highlighted in the following list:


* Create an abstraction for entity renderers.
* Wrap OpenGL functionality needed for rendering.
* Create builders for different render types.
* Wrap the Windows Audio Stream (WASAPI) functionality to access audio endpoints for analysis. WINDOWS
* Wrap the ALSA funcitonality to access audio endpoint (or get a third party lib). LINUX
* Develop fourier analysers for audio data.
