(function(){
	const firebaseConfig = {
    apiKey: "AIzaSyBYmywVN2nqIcZYPSUhoaCf2_kfijCEk1w",
    authDomain: "treeviz-6d06b.firebaseapp.com",
    databaseURL: "https://treeviz-6d06b.firebaseio.com",
    projectId: "treeviz-6d06b",
    storageBucket: "treeviz-6d06b.appspot.com",
    messagingSenderId: "304865929827",
    appId: "1:304865929827:web:0014aa60829543f59aa656",
    measurementId: "G-9SYWR2TTEY"
};

firebase.initializeApp(config);

const preObject = document.getElementById('object');
const dbRefObject = firebase.database().ref().child('object');
dbRefObject.on('value', snap => console.log(snap.val()));



}());


