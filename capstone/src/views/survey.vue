<template>
  <div id="app">
    <form @submit="submitName">
      <div>
        <img src="../assets/Logo-Black.png"><br>
        <p>Please Fill out the Survey</p>
        <input type="text" v-model="newUser.first_Name" placeholder="First Name" required><br>

        <input type="text" v-model="newUser.last_Name" placeholder="Last Name" required><br>

        <input type="text" v-model="newUser.occupation" placeholder="Affiliation (e.g., Tempe State University, Taylor High School)"required><br>

        <input type="text" v-model="newUser.locale" placeholder="City, State, Country"required><br>

        <label for="roles">Choose an Affiliation Role:</label><br>
        <select v-model="newUser.role" class="roles" required>
          <option value="Student(K-12)">Student (K-12)</option>
          <option value="Student(Undergraduate)">Student (Undergraduate)</option>
          <option value="Student(Graduate)">Student (Graduate)</option>
          <option value="Instructor(K-12)">Instructor (K-12)</option>
          <option value="Instructor(Undergraduate)">Instructor (Undergraduate)</option>
          <option value="Instructor(graduate-level)">Instructor (Graduate-Level)</option>
          <option value="Researcher(Bachelors or masters)">Researcher (Bachelors or Masters level)</option>
          <option value="Researcher(PhD Level)">Researcher (PhD Level)</option>
          <option value="Natural Resource Manager, Conservationist, or Practitioner">Natural Resource Manager, Conservationist, or Practitioner</option>
          <option value="Other">Other</option>

        </select>
        <br>
        <br>
        <button type="submit" value="Submit">Submit</button>
      </div>
      <div>
        <ul>
          <li v-for="user of users"
            v-bind:key="user['.key']">
          </li>
        </ul>
      </div>
  </form>
  </div>
</template>

<script>
import { userRef } from '../main';

export default {
  name: 'survey',
  data () {
    return {
      newUser: {
        first_Name: '',
        last_Name: '',
        occupation: '',
        local: '',
        role: ''
      }
    }
  },
  firebase: {
    users: userRef
  },
  methods: {
    submitName() {
      var keyRef = userRef.push( this.newUser );
      this.$router.replace('inputs-vis');
    }
  }
}
</script>

<style scoped>


h1, h2 {
  font-weight: normal;
}

ul {
  list-style-type: none;
  padding: 0;
}

li {
  display: inline-block;
  margin: 0 10px;
}

a {
  color: #42b983;
}

button {
  margin-top: 20px;
  width: 10%;
  cursor: pointer;
}
input {
  margin: 10px 0;
  width: 25%;
  padding: 15px;
}


@-webkit-keyframes fadeIn {
  0% {
    opacity:0;
    transform: scale(0.6);
  }

  100% {
    opacity:100%;
    transform: scale(1);
  }
}

@keyframes fadeIn {
  0% { opacity:0; }
  100% { opacity:100%; }
}
.roles {
  width: 22%;
}
</style>
