import unreal

# Function to spawn an actor of a specified class
def spawn_actor(actor_class, location, rotation):
    # Get the current world
    world = unreal.EditorLevelLibrary.get_editor_world()

    # Define spawn parameters
    spawn_params = unreal.ActorSpawnParameters()
    spawn_params.override_level = world.get_current_level()
    
    # Spawn the actor
    new_actor = world.spawn_actor(actor_class, location, rotation, spawn_params)
    return new_actor

# Example usage
if __name__ == "__main__":
    # Specify the class of the actor you want to spawn (e.g., StaticMeshActor)
    actor_class = unreal.StaticMeshActor
    
    # Define the spawn location and rotation
    location = unreal.Vector(0.0, 0.0, 0.0)
    rotation = unreal.Rotator(0.0, 0.0, 0.0)
    
    # Spawn the actor
    new_actor = spawn_actor(actor_class, location, rotation)
    if new_actor:
        print(f"Successfully spawned actor: {new_actor.get_name()}")
    else:
        print("Failed to spawn actor.")
