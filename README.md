# MIGHTY: Hermite Spline-based Efficient Trajectory Planning #

If you like this project, please consider starring ⭐ the repo!

### **Submitted to the IEEE Robotics and Automation Letters (RA-L)**

| **Trajectory** | **Forest** |
| ------------------------- | ------------------------- |
<a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_complex_benchmarks.gif" width="360" height="240" alt="Complex Benchmarks"></a> | <a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hard_forest.gif" width="360" height="240" alt="Static Forest"></a> |

| **Dynamic Obstacles** | **Long Flight** |
| ------------------------- | ------------------------- |
<a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_dynamic_sim.gif" width="360" height="240" alt="Dynamic Obstacles"></a> | <a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hw_long_flight.gif" width="360" height="240" alt="Hardware Long Flight"></a>

| **Fast Flight 1** | **Fast Flight 2** |
| ------------------------- | ------------------------- |
<a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hw_fast_flight_1.gif" width="360" height="240" alt="Hardware Fast Flight 1"></a> | <a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hw_fast_flight_2.gif" width="360" height="240" alt="Hardware Fast Flight 2"></a>

| **Dynamic Env 1** | **Dynamic Env 2** |
| ------------------------- | ------------------------- |
<a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hw_dynamic_1.gif" width="360" height="240" alt="Hardware Dynamic Env 1"></a> | <a target="_blank" href="https://youtu.be/Pvb-VPUdLvg"><img src="./imgs/mighty_gifs_hw_dynamic_2.gif" width="360" height="240" alt="Hardware Dynamic Env 2"></a>

## Paper

MIGHTY: Hermite Spline-based Efficient Trajectory Planning is available [https://arxiv.org/abs/2511.10822](https://arxiv.org/abs/2511.10822)!

```bibtex
@article{kondo2025mighty,
      title={MIGHTY: Hermite Spline-based Efficient Trajectory Planning}, 
      author={Kota Kondo and Yuwei Wu and Vijay Kumar and Jonathan P. How},
      year={2025},
      eprint={2511.10822},
      archivePrefix={arXiv},
      primaryClass={cs.RO},
      url={https://arxiv.org/abs/2511.10822}, 
}
```

## Video

The full video is available [https://youtu.be/Pvb-VPUdLvg](https://youtu.be/Pvb-VPUdLvg).

## Interactive Demo

If you are interested in an interactive demo of MIGHTY, please switch to the `interactive_demo` branch [https://github.com/mit-acl/mighty/tree/interactive_demo] by running:

```bash
git checkout interactive_demo
```
and follow the setup instructions in the README of that branch.

## Fork

Since you might want to use interactive demos, when you fork this repository, please make sure to also include the `interactive_demo` branch by unselecting the "Copy the main branch only" option.

## Setup

MIGHTY has been tested on both Docker and native installations on Ubuntu 22.04 with ROS 2 Humble.

### Use Docker (Recommended)

1. **Install Docker:**  
   Follow the [official Docker installation guide for Ubuntu](https://docs.docker.com/engine/install/ubuntu/).

2. **Clone the Repository and Navigate to the Docker Folder:**
   ```bash
   mkdir -p ~/code/ws/src
   cd ~/code/ws/src
   git clone https://github.com/mit-acl/mighty.git
   cd src/mighty/docker
   ```

3. **BUILD:**
    - Navigate to the docker folder in your mighty repo (eg. `cd ~/code/ws/src/mighty/docker/`) and run this
      ```bash
      make build
      ```

4. **Run Simulation**
    - Run the following command to start the simulation:
      ```bash
      make run
      ```

<details>
  <summary><b>Useful Docker Commands</b></summary>

  - **Remove all caches:**  
    ```bash
    docker builder prune
    ```

  - **Remove all containers:**  
    ```bash
    docker rm $(docker ps -a -q)
    ```

  - **Remove all images:**  
    ```bash
    docker rmi $(docker images -q)
    ```

</details>

### Native Installation

1. **Clone the Repository and Navigate to the Workspace Folder:**
   ```bash
   mkdir -p ~/code/ws
   cd ~/code/ws
   git clone https://github.com/mit-acl/mighty.git
   cd mighty
   ```

2. **Run the Setup Script:**
   ```bash
   ./setup.sh
   ```
   This script will first install ROS 2 Humble, then MIGHTY and its dependencies. Please note that this script modifies your `~/.bashrc` file.

 3. **Run the Simulation**

    Use the unified simulation launcher script `run_sim.py`:

    ```bash
    cd ~/code/mighty_ws

    # Multi-agent simulation with fake sensing (10 agents)
    python3 src/mighty/scripts/run_sim.py --mode multiagent --setup-bash ~/code/mighty_ws/install/setup.bash

    # Single-agent Gazebo simulation with ACL mapper
    python3 src/mighty/scripts/run_sim.py --mode gazebo --setup-bash ~/code/mighty_ws/install/setup.bash

    # Gazebo with custom goal position
    python3 src/mighty/scripts/run_sim.py --mode gazebo --setup-bash ~/code/mighty_ws/install/setup.bash --goal 100 50 3
    ```

### Simulation Launcher Options

The `run_sim.py` script automatically handles:
- Setting `sim_env` via launch argument (no manual YAML editing needed)
- Launching all required nodes via tmux

<details>
  <summary><b>Multi-Agent Simulation (Fake Sensing)</b></summary>

  ```bash
  # Default: 10 agents in a circle formation
  python3 src/mighty/scripts/run_sim.py --mode multiagent -s ~/code/mighty_ws/install/setup.bash

  # Custom number of agents
  python3 src/mighty/scripts/run_sim.py --mode multiagent -s ~/code/mighty_ws/install/setup.bash --num-agents 5

  # Custom circle radius
  python3 src/mighty/scripts/run_sim.py --mode multiagent -s ~/code/mighty_ws/install/setup.bash --radius 15
  ```
</details>

<details>
  <summary><b>Single-Agent Gazebo Simulation</b></summary>

  ```bash
  # Default goal (305, 0, 3)
  python3 src/mighty/scripts/run_sim.py --mode gazebo -s ~/code/mighty_ws/install/setup.bash

  # Custom goal
  python3 src/mighty/scripts/run_sim.py --mode gazebo -s ~/code/mighty_ws/install/setup.bash --goal 100 50 3

  # Custom start position
  python3 src/mighty/scripts/run_sim.py --mode gazebo -s ~/code/mighty_ws/install/setup.bash --start 5 5 3

  # Different environment
  python3 src/mighty/scripts/run_sim.py --mode gazebo -s ~/code/mighty_ws/install/setup.bash --env easy_forest

  # Enable Gazebo GUI
  python3 src/mighty/scripts/run_sim.py --mode gazebo -s ~/code/mighty_ws/install/setup.bash --gazebo-gui
  ```
</details>

<details>
  <summary><b>All Options</b></summary>

  ```
  --mode, -m          Required. 'multiagent' or 'gazebo'
  --setup-bash, -s    Required. Path to setup.bash
  --goal, -g          Goal position X Y Z for gazebo mode (default: 305 0 3)
  --start, -p         Start position X Y Z for gazebo mode (default: 0 0 3)
  --start-yaw         Start yaw in radians (default: 1.57)
  --num-agents, -n    Number of agents for multiagent mode (default: 10)
  --radius, -r        Circle radius for multiagent formation (default: 10)
  --env, -e           Gazebo environment (default: hard_forest)
  --ros-domain-id     ROS_DOMAIN_ID (default: 7)
  --no-rviz           Disable RViz
  --gazebo-gui        Enable Gazebo GUI
  --dry-run           Print generated YAML without launching
  ```
</details>

### Notes

<details>
  <summary><b>Bag Recording</b></summary>

  - ```bash
    python3 src/mighty/scripts/bag_record.py --bag_number 3
    ```
</details>

<details>
  <summary><b>Goal Command Example</b></summary>

  - ```bash
    ros2 topic pub /NX01/term_goal geometry_msgs/msg/PoseStamped "{header: {stamp: {sec: 0, nanosec: 0}, frame_id: 'map'}, pose: {position: {x: 305.0, y: 0.0, z: 3.0}, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}}}" --once
    ```
</details>
