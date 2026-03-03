extends Node

var sample_rate = 44100.0 
var startingFreq = 440.0
var synth: WaveTableSynth = WaveTableSynth.new()
var playback: AudioStreamPlayback = null # Actual playback stream, assigned in _ready().
var csynth := CppWavetableSynth.new()

@export var wave_type:= WaveTableSynth.WAVE_TYPE.SINEWAVE

@export_enum ("Sine", "Square", "Saw", "Triangle") var Cpp_Wavetype: int = 0


func _ready():
	synth.waveType = synth.WAVE_TYPE.SINEWAVE
	print (synth.waveType)
	synth.waveType = synth.WAVE_TYPE.SAWTOOTHWAVE
	print (synth.waveType)
	var type = csynth.wtype
	print ("type: ", type)
	csynth.wtype = Cpp_Wavetype
	type = csynth.wtype
	print ("type: ", type)

	
	$Player.stream.mix_rate = sample_rate 	# Setting mix rate is only possible before play().
	csynth.prepareToPlay(sample_rate, startingFreq, type)
	#synth.prepareToPlay(sample_rate, startingFreq)

	$Player.play()
	playback = $Player.get_stream_playback()
	
func _process(_delta):
	csynth.render(playback)
	
	#synth.render(playback)
	pass
	


	

#--- UI ---#

func _on_frequency_h_slider_value_changed(value):
	%FrequencyLabel.text = "%d Hz" % value
	csynth.updateFrequency(value)
	#synth.updateFrequency(value)
	

func _on_volume_h_slider_value_changed(value):
	# Use `linear_to_db()` to get a volume slider that matches perceptual human hearing.
	%VolumeLabel.text = "%.2f dB" % linear_to_db(value)
	$Player.volume_db = linear_to_db(value)

#-BUTTONS
func _on_hold_button_button_down():
	csynth.handleInput(true)
	#synth.handleInput(true)
	
func _on_hold_button_button_up():
	csynth.handleInput(false)
	#synth.handleInput(false)

func _on_button_toggled(toggled_on):
	csynth.handleInput(toggled_on)
	#synth.handleInput(toggled_on)
