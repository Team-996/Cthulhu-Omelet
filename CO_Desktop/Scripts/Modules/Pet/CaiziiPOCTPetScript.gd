extends Sprite2D

func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
			print("Sprite clicked!")
			ClientEvent.emit_signal("request_client_startup_event")
