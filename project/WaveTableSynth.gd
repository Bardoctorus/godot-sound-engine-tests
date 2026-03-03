class_name WaveTableSynth

var oscillators = []
var oscillator: WavetableOscillator = null
var WAVETABLE_LENGTH = 64
var waveType: int

enum WAVE_TYPE {
	SINEWAVE,
	SQUAREWAVE,
	SAWTOOTHWAVE,
	TRIANGLEWAVE}
	

	
	
#func initOscillators():
	#oscillators.clear()
	#var OSCILLATOR_COUNT = 5
	#generateSineWaveTable(sineWaveTable)
	#
	#for o in OSCILLATOR_COUNT:
		#var osc = WavetableOscillator.new(sineWaveTable, sampleRate)
		#oscillators.append(osc)
		
func initOscillator(_sampleRate,_starting_freq):
	var sineWaveTable = []
	for i in WAVETABLE_LENGTH:
		sineWaveTable.append(sin(TAU * (i as float / WAVETABLE_LENGTH)))
	oscillator = WavetableOscillator.new(sineWaveTable, _sampleRate, _starting_freq)
	print("oscillator type: %s", oscillator)
		
func handleInput(message: bool):
	if message == true:
		oscillator.start()
	else: oscillator.stop()
	
func updateFrequency(freq):
	oscillator.update(freq)
		
		

func prepareToPlay(_sampleRate, _starting_freq):	
	initOscillator(_sampleRate,_starting_freq)
	
func render(playback: AudioStreamGeneratorPlayback):
	if oscillator.isPlaying:
		for f in playback.get_frames_available():
			var sample = oscillator.getSample()
			playback.push_frame(Vector2(sample, sample))
	
	
