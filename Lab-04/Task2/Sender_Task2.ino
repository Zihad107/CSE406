#include <painlessMesh.h>

// Mesh network configuration
#define MESH_PREFIX     "cse406"       // Network name (all nodes must match)
#define MESH_PASSWORD   "summer25"     // Network password (same on all nodes)
#define MESH_PORT       5555           // Port number used for communication

Scheduler userScheduler;
painlessMesh mesh;

// === Target Node ID ===
// The Node ID of the device you want to send messages to
uint32_t targetNodeId = 1163270074;

// === Message sending function ===
// Declaring a task that calls sendMessage every 1 second, repeatedly
void sendMessage(); 
Task taskSendMessage(TASK_SECOND * 1 , TASK_FOREVER, &sendMessage);

// === Function that sends message to target node ===
void sendMessage() {
  // Declare msg inside this function
  String msg = "Hello from Node ";
  msg += mesh.getNodeId();   // Adds the unique Node ID
  msg += " 🚀 | Mesh network communication successful!";

  // Sends message directly to the target node
  bool success = mesh.sendSingle(targetNodeId, msg);
  if (success) {
    Serial.printf("📤 Message sent to %u ✅\n", targetNodeId);
  } else {
    Serial.printf("❌ Failed to send to %u\n", targetNodeId);
  }

  // Change interval randomly between 1–5 seconds for the next send
  taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5));
}

// === Callback when message is received ===
void receivedCallback(uint32_t from, String &msg) {
  Serial.println("====================================");
  Serial.printf("📩 Message received!\n");
  Serial.printf("👤 Sender Node ID : %u\n", from);
  Serial.printf("✉️  Message        : %s\n", msg.c_str());
  Serial.println("====================================\n");
}

// === Callback when a new device connects ===
void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("🔗 Connected with Node ID: %u\n", nodeId);
}

// === Callback when the network topology changes (node joined or left) ===
void changedConnectionCallback() {
  Serial.println("🔄 Connection list changed");
}

// === Callback when this node's time gets synced with the mesh ===
void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("⏱️ Time adjusted. Offset = %d\n", offset);
}

// === Arduino setup function ===
void setup() {
  Serial.begin(115200);  // Start Serial Monitor
  mesh.setDebugMsgTypes(ERROR | STARTUP);  // Enable basic debug messages

  // Initialize mesh network with credentials and scheduler
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);

  // Set all the callback functions
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  // Schedule the message sending task
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();

  // Print this device's unique Node ID
  Serial.printf("✅ Device Ready | My Node ID: %u\n", mesh.getNodeId());
}

// === Arduino loop function ===
// Updates mesh status regularly
void loop() {
  mesh.update();
}
