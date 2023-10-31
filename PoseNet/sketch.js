// let capture;
// let poseNet;
// let noseX, noseY;
// let singlePose;
// function setup() {
//   createCanvas(800, 500);
//   capture = createCapture(VIDEO);
//   capture.hide();
//   poseNet = ml5.poseNet(capture, modelLoaded);
//   poseNet.on("pose", recievedPoses);
// }
// function recievedPoses(poses) {
//   console.log(poses);
//   if (poses.length > 0) {
//     singlePose = poses[0].pose;
//     noseX = singlePose.nose.x;
//     noseY = singlePose.nose.y;
//   }
//   console.log(noseX + " " + noseY);
// }

// function modelLoaded() {
//   console.log("Model has loaded");
// }
// function draw() {
//   image(capture, 0, 0, 800, 600);
//   fill(255,0, 0);
//   ellipse(noseX, noseY, 30, 30)
// }
let capture;
let posenet;
let noseX,noseY;
let reyeX,reyeY;
let leyeX,leyeY;
let singlePose,skeleton;
let actor_img;
let specs,smoke;

function setup() {
    createCanvas(800, 500);
    capture = createCapture(VIDEO)
    capture.hide();

    posenet = ml5.poseNet(capture, modelLoaded);
    posenet.on('pose',receivedPoses);

    // actor_img = loadImage('images/shahrukh.png');
    // specs = loadImage('images/spects.png');
    // smoke = loadImage('images/cigar.png');

}

function receivedPoses(poses){
    console.log(poses);

    if(poses.length > 0){
        singlePose = poses[0].pose;
        skeleton = poses[0].skeleton;
    }
}

function modelLoaded() {
    console.log('Model has loaded');
}

function draw() {

    // images and videos(webcam)
    image(capture, 0, 0, capture.width,capture.height);
    fill(255,0,0);

    if(singlePose){
        for(let i=0; i<singlePose.keypoints.length; i++){
            ellipse(singlePose.keypoints[i].position.x, singlePose.keypoints[i].position.y,20);
        }
        stroke(255,255,255);
        strokeWeight(5);
        for(let j=0; j<skeleton.length; j++){
            line(skeleton[j][0].position.x, skeleton[j][0].position.y, skeleton[j][1].position.x, skeleton[j][1].position.y)
        }

        //image(specs,singlePose.nose.x-35,singlePose.nose.y-50,80,80);
        //image(smoke,singlePose.nose.x-35,singlePose.nose.y+10,40,40);

        
    }
}