// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import firebase from 'firebase'
import App from './App'
import router from './router'

Vue.config.productionTip = false;

let app = '';

firebase.initializeApp({
    apiKey: "AIzaSyBlhe49hu63T-V7vuy1_NSYmOXFXzNqLm8",
    authDomain: "acgcamodel.firebaseapp.com",
    databaseURL: "https://acgcamodel.firebaseio.com",
    projectId: "acgcamodel",
    storageBucket: "acgcamodel.appspot.com",
    messagingSenderId: "949804227890",
    appId: "1:949804227890:web:ddd6263dec9eab0bfacb2b",
    measurementId: "G-EPKM1H65GM"
});

firebase.auth().onAuthStateChanged(() => {
  if (!app) {
    app = new Vue({
      router,
      render: h => h(App)
    }).$mount('#app');
  }
});
