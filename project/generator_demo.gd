extends Node

var sample_rate = 44100.0 
var startingFreq = 440.0
var synth: WaveTableSynth = WaveTableSynth.new()

var playback: AudioStreamPlayback = null # Actual playback stream, assigned in _ready().



func _ready():
	print("synth type %s", synth)

	var example := ExampleClass.new()
	example.print_type(example)
	
	$Player.stream.mix_rate = sample_rate 	# Setting mix rate is only possible before play().
	synth.prepareToPlay(sample_rate, startingFreq)
	$Player.play()
	playback = $Player.get_stream_playback()
	
func _process(_delta):
	synth.render(playback)
	

#--- UI ---#

func _on_frequency_h_slider_value_changed(value):
	%FrequencyLabel.text = "%d Hz" % value
	synth.updateFrequency(value)
	

func _on_volume_h_slider_value_changed(value):
	# Use `linear_to_db()` to get a volume slider that matches perceptual human hearing.
	%VolumeLabel.text = "%.2f dB" % linear_to_db(value)
	$Player.volume_db = linear_to_db(value)

#-BUTTONS
func _on_hold_button_button_down():
	synth.handleInput(true)
	
func _on_hold_button_button_up():
	synth.handleInput(false)

func _on_button_toggled(toggled_on):
	synth.handleInput(toggled_on)
