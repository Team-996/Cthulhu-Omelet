extends Sprite2D

signal health_depleted
signal health_changed(old_value, new_value)

var health = 10
var speed = 400
var angular_speed = PI
func _init():
	print("Hello world!")

func _ready() -> void:
	var timer = get_node("Timer") # like event bind ?
	timer.timeout.connect(_on_timer_timeout)
	
func _process(delta: float) -> void:
	var direction = 0
	if Input.is_action_pressed("ui_left"):
		direction = -1
	if Input.is_action_pressed("ui_right"):
		direction = 1
	rotation += angular_speed * direction * delta
	
	var velocity = Vector2.ZERO
	if Input.is_action_pressed("ui_up"):
		velocity = Vector2.UP.rotated(rotation) * speed
	# var velocity = Vector2.UP.rotated(rotation) * speed
	position += velocity * delta
	
func take_damage(amount: int )-> void:
	var old_health = health
	health -= amount
	health_changed.emit(old_health,health)
	
func _on_button_pressed() -> void:
	set_process(not is_processing())
	
func _on_timer_timeout() ->void:
	visible = not visible
