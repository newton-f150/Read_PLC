use axum::{
    routing::get,
    Router,
    Json,
};
use serde::Serialize;
use tokio::time::{sleep, Duration};

#[derive(Serialize)]
struct PlcData {
    motor_speed: u32,
    temperature: u32,
    pressure: u32,
    conveyor_status: bool,
}

async fn read_plc_data() -> PlcData {
    sleep(Duration::from_millis(100)).await;
    PlcData {
        motor_speed: 123,
        temperature: 75,
        pressure: 40,
        conveyor_status: true,
    }
}

async fn plc_endpoint() -> Json<PlcData> {
    let data = read_plc_data().await;
    Json(data)
}

#[tokio::main]
async fn main() {
    let app = Router::new().route("/plc", get(plc_endpoint));

    println!("Server running on http://127.0.0.1:3000");
    axum::Server::bind(&"127.0.0.1:3000".parse().unwrap())
        .serve(app.into_make_service())
        .await
        .unwrap();
}


// let listener = tokio::net::TcpListener::bind(&addr).await.unwrap;