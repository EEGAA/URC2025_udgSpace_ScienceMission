#include <ros/ros.h>
#include <std_msgs/Bool.h>

class Esp32ControlNode {
public:
    Esp32ControlNode() {
        // Inicializar publishers y subscribers con std_msgs::Bool
        led_pub_ = nh_.advertise<std_msgs::Bool>("led_command", 10);
        button_sub_ = nh_.subscribe("button_state", 10, &Esp32ControlNode::buttonCallback, this);
        
        // Estado inicial
        current_state_ = WAITING_FOR_BUTTON;
        led_on_ = false;
        led_changed_ = false;
    }

    void run() {
        ros::Rate rate(10); // 10 Hz
        
        while (ros::ok()) {
            // Ejecutar la máquina de estados
            executeStateMachine();
            
            // Publicar el estado del LED si ha cambiado
            if (led_changed_) {
                std_msgs::Bool msg;
                msg.data = led_on_;
                led_pub_.publish(msg);
                led_changed_ = false;
                ROS_INFO("LED state changed to: %s", led_on_ ? "ON" : "OFF");
            }
            
            ros::spinOnce();
            rate.sleep();
        }
    }

private:
    enum State {
        WAITING_FOR_BUTTON,
        LED_ON
    };
    
    ros::NodeHandle nh_;
    ros::Publisher led_pub_;
    ros::Subscriber button_sub_;
    
    State current_state_;
    bool button_pressed_;
    bool led_on_;
    bool led_changed_;
    
    void buttonCallback(const std_msgs::Bool::ConstPtr& msg) {
        button_pressed_ = msg->data;
    }
    
    void executeStateMachine() {
        switch (current_state_) {
            case WAITING_FOR_BUTTON:
                if (button_pressed_) {
                    // Encender LED y cambiar estado
                    led_on_ = true;
                    led_changed_ = true;
                    current_state_ = LED_ON;
                    ROS_INFO("Button pressed - turning LED ON");
                }
                break;
                
            case LED_ON:
                if (!button_pressed_) {
                    // Apagar LED y volver al estado inicial
                    led_on_ = false;
                    led_changed_ = true;
                    current_state_ = WAITING_FOR_BUTTON;
                    ROS_INFO("Button released - turning LED OFF");
                }
                break;
        }
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "esp32_control_node");
    
    Esp32ControlNode node;
    node.run();
    
    return 0;
}
