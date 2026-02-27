# Messing with Godot Audio

This started as the Audio Generator GDScript example, was extended into a GDscript Wavetable sine synth, and the next step was to try and move it wholesale to cpp as an in between step to getting a realtime audio system I was happy with. 

Then I saw [this example code](https://docs.godotengine.org/en/stable/engine_details/engine_api/custom_audiostreams.html) which has somewhat convinced me that jumping straight to a custom audio stream might be the best option for now. 