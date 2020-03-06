import Vue from 'vue'
import firebase from 'firebase'
import App from './App.vue'
import router from './router'
import axios from 'axios'



Vue.config.productionTip = false

//let app = '';

let app = firebase.initializeApp({
  apiKey: "AIzaSyC5nS9CfR_UvmEdLMArhVKSw7MNDOk_lN4",
  authDomain: "fir-vue-cd426.firebaseapp.com",
  databaseURL: "https://fir-vue-cd426.firebaseio.com",
  projectId: "fir-vue-cd426",
  storageBucket: "fir-vue-cd426.appspot.com",
  messagingSenderId: "717209956436",
  appId: "1:717209956436:web:e668b20e40722c894efdc1",
  measurementId: "G-1WSQ0XJDDE"
});

export const db = app.database();
export const userRef = db.ref('users');

firebase.auth().onAuthStateChanged(() => {
  if (!app) {
    app = new Vue({
      router,
      render: h => h(App)
    }).$mount('#app');
  }
});
app = new Vue({
  router,
  render: h => h(App)
}).$mount('#app');
